#include <QFileDialog>
#include <QGridLayout>
#include <QDebug>
#include "Visualizer.h"
#include "STLReader.h"
#include "OBJReader.h"
#include "OBJWriter.h"
#include "STLWriter.h"
#include "DataWriter.h"
#include "QualityAnalysis.h"

Visualizer::Visualizer(QWidget* parent) : QMainWindow(parent)
{
    setupUi();
    connect(loadFile, &QPushButton::clicked, this, &Visualizer::onLoadFileClick);
}

Visualizer::~Visualizer()
{
}

void Visualizer::setupUi()
{
    loadFile = new QPushButton("Load File", this);
    openglWidgetInput = new OpenGlWidget(this);
    progressBar = new QProgressBar(this);
    containerWidget = new QWidget(this);
    firstCheckBox = new QCheckBox("Bounding Box", containerWidget);
    secondCheckBox = new QCheckBox("Aspect Ratio", containerWidget);
    thirdCheckBox = new QCheckBox("Orthogonality", containerWidget);
    param1textbox = new QTextEdit("", containerWidget);
    param2textbox = new QTextEdit("", containerWidget);
    param3textbox = new QTextEdit("", containerWidget);
    param4textbox = new QTextEdit("", containerWidget);
    param5textbox = new QTextEdit("", containerWidget);
    Parameter1 = createReadOnlyTextEdit("No. of Triangles", containerWidget);
    Parameter2 = createReadOnlyTextEdit("Surface Area", containerWidget);
    Parameter3 = createReadOnlyTextEdit("Triangle Density", containerWidget);
    Parameter4 = createReadOnlyTextEdit("ObjectLength", containerWidget);
    Parameter5 = createReadOnlyTextEdit("No. of Vertices", containerWidget);


    QString buttonStyle = "QPushButton {"
        "    background-color: #4CAF50;"
        "    color: white;"
        "    border: none;"
        "    padding: 10px 20px;"
        "    font-size: 16px;"
        "    border-radius: 5px;"
        "    border: 2px solid black;"
        "}"
        "QPushButton:hover {"
        "    background-color: #45a049;"
        "}"
        "QPushButton:pressed {"
        "    background-color: #3e8e41;"
        "}";

    QString widgetStyle = "QWidget {"
        "    background-color: #333;"
        "    color: #f5f5f5;"
        "}";

    QString containerStyle = "background-color: white; color: black;";

    loadFile->setStyleSheet(buttonStyle);
    this->setStyleSheet(widgetStyle);
    containerWidget->setStyleSheet(containerStyle);

    QVBoxLayout* containerLayout = new QVBoxLayout(containerWidget);
    containerLayout->addWidget(firstCheckBox);
    containerLayout->addWidget(secondCheckBox);
    containerLayout->addWidget(thirdCheckBox);
    containerLayout->addWidget(Parameter1);
    containerLayout->addWidget(param1textbox);
    containerLayout->addWidget(Parameter2);
    containerLayout->addWidget(param2textbox);
    containerLayout->addWidget(Parameter3);
    containerLayout->addWidget(param3textbox);
    containerLayout->addWidget(Parameter4);
    containerLayout->addWidget(param4textbox);
    containerLayout->addWidget(Parameter5);
    containerLayout->addWidget(param5textbox);

    QGridLayout* layout = new QGridLayout();
    QWidget* centralWidget = new QWidget(this);

    layout->addWidget(loadFile, 0, 0, 1, 3);
    layout->addWidget(openglWidgetInput, 1, 0, 1, 3);
    layout->addWidget(progressBar, 2, 0, 1, 6);
    layout->addWidget(containerWidget, 0, 3, 2, 3);

    layout->setContentsMargins(20, 20, 20, 20);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
}

void Visualizer::onLoadFileClick()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("files (*.stl *.obj)"));
    if (!fileName.isEmpty())
    {
        inputFilePath = fileName;
        triangulation = readFile(inputFilePath);
        OpenGlWidget::Data data = convertTrianglulationToGraphicsObject(triangulation);
        openglWidgetInput->setData(data);

        QualityAnalysis::QualityAnalysis qualityAnalysis;
        qDebug() << "-----------------------------------------" << qualityAnalysis.drawBoundingBox(triangulation);

        // Update the parameter values after the object is read
        param1Value = triangulation.Triangles.size();  // Example: No. of Triangles
        param2Value = qualityAnalysis.surfaceArea(triangulation);  // Surface Area calculation method
        param3Value = qualityAnalysis.triangleDensity(triangulation);  // Triangle Density calculation method
        param4Value = qualityAnalysis.objectLength(triangulation);  // Volume calculation method
        param5Value = qualityAnalysis.numberOfVertices(triangulation);  // Example: No. of Vertices

        // Update the textboxes with the new values
        param1textbox->setText(QString::number(param1Value));
        param2textbox->setText(QString::number(param2Value));
        param3textbox->setText(QString::number(param3Value));
        param4textbox->setText(QString::number(param4Value));
        param5textbox->setText(QString::number(param5Value));

    }
}

Triangulation Visualizer::readFile(const QString& filePath)
{
    Triangulation tri;
    if (filePath.endsWith(".stl", Qt::CaseInsensitive))
    {
        STLReader reader;
        reader.read(filePath.toStdString(), tri);
    }
    else if (filePath.endsWith(".obj", Qt::CaseInsensitive))
    {
        OBJReader reader;
        reader.read(filePath.toStdString(), tri);
    }
    return tri;
}

void Visualizer::writeFile(const QString& filePath, const Triangulation& tri)
{
    if (filePath.endsWith(".stl", Qt::CaseInsensitive))
    {
        STLWriter writer;
        writer.Write(filePath.toStdString(), tri, progressBar);
    }
    else if (filePath.endsWith(".obj", Qt::CaseInsensitive))
    {
        ObjWriter writer;
        writer.Write(filePath.toStdString(), tri, progressBar);
    }
}

int Vcount = 0;

OpenGlWidget::Data Visualizer::convertTrianglulationToGraphicsObject(const Triangulation& inTriangulation)
{
    OpenGlWidget::Data data;
    for each (Triangle triangle in inTriangulation.Triangles)
    {
        for each (Point point in triangle.Points())
        {
            data.vertices.push_back(inTriangulation.UniqueNumbers[point.X()]);
            data.vertices.push_back(inTriangulation.UniqueNumbers[point.Y()]);
            data.vertices.push_back(inTriangulation.UniqueNumbers[point.Z()]);
        }

        Point normal = triangle.Normal();
        for (size_t i = 0; i < 3; i++)
        {
            data.normals.push_back(inTriangulation.UniqueNumbers[normal.X()]);
            data.normals.push_back(inTriangulation.UniqueNumbers[normal.Y()]);
            data.normals.push_back(inTriangulation.UniqueNumbers[normal.Z()]);
        }
        progressBar->setValue(Vcount);
        progressBar->setRange(0, inTriangulation.Triangles.size() - 1);
        Vcount++;
    }
    return data;
}

QTextEdit* Visualizer::createReadOnlyTextEdit(const QString& text, QWidget* parent)
{
    QTextEdit* textEdit = new QTextEdit(text, parent);
    textEdit->setReadOnly(true);

    // Center-align the text
    QTextCursor cursor = textEdit->textCursor();
    QTextBlockFormat format;
    format.setAlignment(Qt::AlignCenter);
    cursor.select(QTextCursor::Document);
    cursor.mergeBlockFormat(format);
    textEdit->setTextCursor(cursor);

    // Apply a basic style
    textEdit->setStyleSheet("QTextEdit { color: black; background-color: #f0f0f0; font-size: 14px; }");

    return textEdit;
}



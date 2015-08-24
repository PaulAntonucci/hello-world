#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "QFileDialog"
#include "QFile"
#include "QMessageBox"
#include "QTextStream"
#include "QChar"
#include "QByteArray"
#include "QString"

#include "read_write_globals.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_quitButton_clicked()
{
    qApp->quit();
}

void MainWindow::on_actionOpen_triggered()
{
    int i,j,k;
    QString toTranslate;
    QString fileName = QFileDialog::getOpenFileName(this,"Open File",
                             QString(), QString());
    QByteArray byteArray;
    //QDataStream dataStream;
    //if(!fileName.isEmpty()) {

    QFile file(fileName);
    defaultNameForFileToWrite = QFileInfo(file).baseName();
    defaultNameForFileToWrite.append(".txt");

        /*QString savefileName = QFileDialog::getSaveFileName(this,"Save File",
                QString("~/").append(defaultNameForFileToWrite), QString());
        if( !savefileName.open(QIODevice::WriteOnly))  QMessageBox::critical(this, "Error", "Could not open write file");
        return; */


    if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, "Error", "Could not open read file");
            return;
    }
        //dataStream.setDevice(&file);
        //QTextStream in(&file);
    byteArray = file.readAll();
    int numBytes = byteArray.length();
    //file.seek(numBytes - 100 * 8); // look 10 doubles back into array, index is 1 less then byte count


    QDataStream ds(&file);
        //numBytes = ds.
    ds.setByteOrder(QDataStream::LittleEndian);
        //ds.skipRawData(numBytes).

        //file.rea
        //toTranslate = in.readAll();
        //toTranslate.prepend("$");
        //toTranslate.append("!");
        //ui->textEdit->setText((toTranslate));
        //ui->hexOutput->setText(toTranslate);

   //}
    //fread(SavePanel, sizeof(Panelpar), structs, filepointer)

    file.seek(0);
    i = sizeof(Tunefrequencypar);
    j = sizeof(panelpar);
    ///ds.s
    panelpar p;             ds >> p;
    tunefrequencypar p0;    ds >> p0;
    adjustparameterpar p1;  ds >> p1;
    setfieldspar p2;        ds >> p2;
    setsequencepar p3;      ds >> p3;
    setwaveformpar p4;      ds >> p4;
    setenvironmentpar p5;   ds >> p5;
    setsamplepar p6;        ds >> p6;
    reservedpar p7;
    // There are 14 of these things read in Jen's code - most of which are ignored. This should get us to the start of data area
    // Oh ho !!  But the "reservedpar" is  read twice !
    for(i=0;i<7;i++) ds>>p7;

    // what to keep: p Span, counts, sides (if not = 1), interval excitation frequency, (target), actual
    // p1: expansion, flow 1 2 3 4, pressure, protectiond, protectionw (delay, width), unloadd, unloadw (discharge delay, width)
    // p6 flows and gasses

    //file.seek(numBytes - 100 * 8); // look 10 doubles back into array, index is 1 less then byte count

    // Something to keep in mind:  s.skipbytes will skip the bytes in the DtaStream object
    ui->hexOutput->appendPlainText(byteArray.toHex());

    //byteArray.replace( (char)0,QByteArray());

    // instead of this, get rid of all control characters
    // e.g.

    for(i=0;i< byteArray.length(); i++) {
         j = byteArray[i];
         if((j < 0x20) || (j >= 0x7f))
            byteArray[i] = 0x20;
    }
    //ui->textEdit->append(QString(byteArray));

    double dataArray[10000];
    int index;
    char charArray[100];
    ui->plainTextEdit->appendPlainText(QString(byteArray));
    //ds.setByteOrder(QDataStream::LittleEndian);
    int limit;
    limit = p4.counts;
    if(limit > 10000) limit = 10000;
    for(i=0;i<limit;i++){
        ds >>dataArray[i];
    }
        //index = (byteArray.length())-9 - 8* i;
        /*
            QDataStream & QDataStream::operator>> ( qint64 & i )
                void QDataStream::setByteOrder ( ByteOrder bo )
        */
        //j = byteArray.at(i);
        //ui->hexOutput->append(QByteArray::toHex(j);
        //ui->hexOutput->append(j);
    file.close();
    QString saveFileName = QFileDialog::getSaveFileName(this,"Save File",
            QString("~/").append(defaultNameForFileToWrite), QString());
    QFile outfile(saveFileName);
    if( !outfile.open(QIODevice::WriteOnly)) {
        QMessageBox::critical(this, "Error", "Could not open write file");
        return;
    }
    QTextStream txt(&outfile);

    defaultNameForFileToWrite.chop(4);
    defaultNameForFileToWrite.append(".dat");
    txt << QString("#Scan From FTM I Jens's Code\t")<<defaultNameForFileToWrite <<QString ("\n");
    txt << QString("#Shots\t") << p.actual << QString("\t\n");
    txt << QString("#Probe freq\t") << QString::number(p.excfreq, 'f', 4) << QString("\tMHz\n");
    txt << QString("#FID interval\t") << QString::number(p.interval, 'f',4) << QString("\tus\n");
    txt << QString("#FID points\t") << p4.counts << QString("\n");
    txt << QString("#FID span\t") << p.span << QString("\tus\n");
    if(p.sides !=1) txt <<QString ("#Sides \t") <<p.sides << QString ("\n");

    txt << QString("#Expansion\t") << p1.expansion << QString("\tus\n");
    txt << QString("#Flow 1\t") << p1.flow1 << QString("\t\n");
    txt << QString("#Flow 2\t") << p1.flow2 << QString("\t\n");
    txt << QString("#Flow 3\t") << p1.flow3 << QString("\t\n");
    txt << QString("#Flow 4\t") << p1.flow4 << QString("\t\n");
    txt << QString("#Pressure\t") << p1.pressure << QString("\tkPa\n");
    txt << QString("#Protection D\t") << p1.protectiond << QString("\tus\n");
    txt << QString("#Protection W\t") << p1.protectionw << QString("\tus\n");
    txt << QString("#Unload D\t") << p1.unloadd << QString("\tus\n");
    txt << QString("#Unload W\t") << p1.unloadw << QString("\tus\n");



    txt.setRealNumberNotation(QTextStream::ScientificNotation);
    txt.setRealNumberPrecision(12);
    txt << QString ("\nfid_data");
    for(i=0;i<limit;i++){
        txt <<QString("\n") <<dataArray[i];
    }
    txt.flush();
    outfile.close();


}

QTextStream scan_header(QTextStream txt){/*
     txt << QString("#Expansion\t") << p1.expansion << QString("\t\n");
     txt << QString("#Flow 1\t") << p1.flow << QString("\t\n");
     txt << QString("#Flow 2\t") << p1.expansion << QString("\t\n");
     txt << QString("#Flow 3\t") << p1.expansion << QString("\t\n");
     txt << QString("#Flow 4\t") << p1.expansion << QString("\t\n");
     txt << QString("#Pressure\t") << p1.expansion << QString("\t\n");
     txt << QString("#Protection D\t") << p1.expansion << QString("\t\n");
     txt << QString("#Protection W\t") << p1.expansion << QString("\t\n");
     txt << QString("#Unload D\t") << p1.expansion << QString("\t\n");
     txt << QString("#Unload W\t") << p1.expansion << QString("\t\n");
/*   // p1: expansion, flow 1 2 3 4, pressure, protectiond, protectionw
 *(delay, width), unloadd, unloadw (discharge delay, width)
 *
 *


    t << QString("#Scan\t") << number() << QString("\t\n");
    t << QString("#Date\t") << timeStamp().toString() << QString("\t\n");
    t << QString("#Shots\t") << completedShots() << QString("\t\n");
    t << QString("#Cavity freq\t") << ftFreq() << QString("\tMHz\n");
    t << QString("#Tuning Voltage\t") << tuningVoltage() << QString("\tmV\n");
    t << QString("#Attenuation\t") << attenuation() << QString("\tdB\n");
    t << QString("#Dipole Moment\t") << dipoleMoment() << QString("\tD\n");
    t << QString("#Cavity Voltage\t") << cavityVoltage() << QString("\tmV\n");

    t << QString("#Protection Delay\t") << protectionDelayTime() << QString("\tus\n");
    t << QString("#Scope Delay\t") << scopeDelayTime() << QString("\tus\n");

    t << QString("#DC enabled\t") << pulseConfiguration().at(1).enabled << QString("\t\n");
    t << QString("#DR enabled\t") << pulseConfiguration().at(3).enabled << QString("\t\n");
    t << QString("#DR freq\t") << drFreq() << QString("\tMHz\n");
    t << QString("#DR power\t") << drPower() << QString("\tdBm\n");
    t << QString("#Probe freq\t") << fid().probeFreq() << QString("\tMHz\n");
    t << QString("#FID spacing\t") << fid().spacing() << QString("\ts\n");
    t << QString("#FID points\t") << fid().size() << QString("\t\n");
    t << QString("#Rep rate\t") << repRate() << QString("\tHz\n");
    t << QString("#Pressure\t") << pressure() << QString("\tkTorr\n");
*/

}



void MainWindow::on_actionSave_triggered()
{




}

/********************************************************************************
** Form generated from reading UI file 'bamwindow.ui'
**
** Created: Mon Mar 18 16:41:02 2013
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BAMWINDOW_H
#define UI_BAMWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QTableWidget>
#include <QtGui/QTextEdit>
#include <QtGui/QToolBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_bamWindow
{
public:
    QAction *actionLoad;
    QAction *actionSave;
    QAction *actionAbout;
    QWidget *centralWidget;
    QTabWidget *tabWidget_2;
    QWidget *crossTab;
    QToolBox *resultToolbox;
    QWidget *page_3;
    QGroupBox *resultsGroup;
    QPlainTextEdit *outputBox;
    QLabel *label_10;
    QWidget *page_4;
    QCustomPlot *currentPlot;
    QWidget *page_5;
    QTabWidget *tabWidget;
    QWidget *tab_1;
    QCustomPlot *nprodPlot;
    QWidget *tab_2;
    QCustomPlot *diffNprodPlot;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QFrame *line_2;
    QProgressBar *progressBar;
    QToolBox *inputToolbox;
    QWidget *targetPage;
    QGroupBox *targetGroup;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label;
    QDoubleSpinBox *thickness;
    QDoubleSpinBox *thicknessError;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_4;
    QDoubleSpinBox *halflife;
    QDoubleSpinBox *halflifeError;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_5;
    QDoubleSpinBox *tm;
    QDoubleSpinBox *tmError;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_6;
    QDoubleSpinBox *tw;
    QDoubleSpinBox *twError;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_7;
    QDoubleSpinBox *reltd;
    QDoubleSpinBox *reltdError;
    QWidget *page_2;
    QGroupBox *inputGroup;
    QTextEdit *inputBox;
    QLabel *label_8;
    QWidget *page;
    QGroupBox *currentGroup;
    QLineEdit *currentPath;
    QPushButton *browseButton;
    QLabel *label_9;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *calButton;
    QPushButton *currentButton;
    QPushButton *nprodButton;
    QPushButton *closeButton;
    QSpacerItem *horizontalSpacer_2;
    QWidget *effTab;
    QTableWidget *eff_inputTable;
    QTableWidget *eff_sourceTable;
    QWidget *layoutWidget3;
    QGridLayout *gridLayout;
    QLabel *detLabel;
    QComboBox *eff_detCombo;
    QLabel *eff_geomLabel;
    QDoubleSpinBox *eff_geomBox;
    QPushButton *eff_calButton;
    QMenuBar *menuBar;
    QMenu *menuHelp;
    QMenu *menu_File;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *bamWindow)
    {
        if (bamWindow->objectName().isEmpty())
            bamWindow->setObjectName(QString::fromUtf8("bamWindow"));
        bamWindow->resize(853, 605);
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(10);
        bamWindow->setFont(font);
        bamWindow->setDockOptions(QMainWindow::AllowTabbedDocks|QMainWindow::AnimatedDocks);
        actionLoad = new QAction(bamWindow);
        actionLoad->setObjectName(QString::fromUtf8("actionLoad"));
        actionLoad->setEnabled(true);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/stuff/new.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionLoad->setIcon(icon);
        actionLoad->setIconVisibleInMenu(true);
        actionSave = new QAction(bamWindow);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        actionSave->setEnabled(true);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/stuff/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon1);
        actionSave->setShortcutContext(Qt::ApplicationShortcut);
        actionSave->setSoftKeyRole(QAction::NoSoftKey);
        actionSave->setIconVisibleInMenu(true);
        actionAbout = new QAction(bamWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        centralWidget = new QWidget(bamWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        tabWidget_2 = new QTabWidget(centralWidget);
        tabWidget_2->setObjectName(QString::fromUtf8("tabWidget_2"));
        tabWidget_2->setGeometry(QRect(10, 10, 841, 541));
        crossTab = new QWidget();
        crossTab->setObjectName(QString::fromUtf8("crossTab"));
        resultToolbox = new QToolBox(crossTab);
        resultToolbox->setObjectName(QString::fromUtf8("resultToolbox"));
        resultToolbox->setGeometry(QRect(430, 10, 401, 361));
        QFont font1;
        font1.setPointSize(10);
        resultToolbox->setFont(font1);
        page_3 = new QWidget();
        page_3->setObjectName(QString::fromUtf8("page_3"));
        page_3->setGeometry(QRect(0, 0, 401, 274));
        resultsGroup = new QGroupBox(page_3);
        resultsGroup->setObjectName(QString::fromUtf8("resultsGroup"));
        resultsGroup->setGeometry(QRect(20, 20, 351, 231));
        outputBox = new QPlainTextEdit(resultsGroup);
        outputBox->setObjectName(QString::fromUtf8("outputBox"));
        outputBox->setGeometry(QRect(10, 60, 331, 161));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Courier 10 Pitch"));
        font2.setPointSize(9);
        font2.setBold(false);
        font2.setItalic(false);
        font2.setWeight(50);
        outputBox->setFont(font2);
        outputBox->setStyleSheet(QString::fromUtf8("font: 9pt \"Courier 10 Pitch\";"));
        label_10 = new QLabel(resultsGroup);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(10, 30, 331, 20));
        label_10->setAlignment(Qt::AlignCenter);
        resultToolbox->addItem(page_3, QString::fromUtf8("Crosssections"));
        page_4 = new QWidget();
        page_4->setObjectName(QString::fromUtf8("page_4"));
        page_4->setGeometry(QRect(0, 0, 401, 274));
        currentPlot = new QCustomPlot(page_4);
        currentPlot->setObjectName(QString::fromUtf8("currentPlot"));
        currentPlot->setGeometry(QRect(10, 20, 381, 231));
        resultToolbox->addItem(page_4, QString::fromUtf8("Current Plot"));
        page_5 = new QWidget();
        page_5->setObjectName(QString::fromUtf8("page_5"));
        page_5->setGeometry(QRect(0, 0, 401, 274));
        tabWidget = new QTabWidget(page_5);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(10, 0, 381, 261));
        tab_1 = new QWidget();
        tab_1->setObjectName(QString::fromUtf8("tab_1"));
        nprodPlot = new QCustomPlot(tab_1);
        nprodPlot->setObjectName(QString::fromUtf8("nprodPlot"));
        nprodPlot->setGeometry(QRect(10, 10, 361, 211));
        tabWidget->addTab(tab_1, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        diffNprodPlot = new QCustomPlot(tab_2);
        diffNprodPlot->setObjectName(QString::fromUtf8("diffNprodPlot"));
        diffNprodPlot->setGeometry(QRect(10, 10, 351, 211));
        tabWidget->addTab(tab_2, QString());
        resultToolbox->addItem(page_5, QString::fromUtf8("Produced Nuclei Plot"));
        layoutWidget = new QWidget(crossTab);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 440, 801, 41));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        line_2 = new QFrame(layoutWidget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_2);

        progressBar = new QProgressBar(layoutWidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(24);

        verticalLayout->addWidget(progressBar);

        inputToolbox = new QToolBox(crossTab);
        inputToolbox->setObjectName(QString::fromUtf8("inputToolbox"));
        inputToolbox->setGeometry(QRect(1, 11, 421, 361));
        inputToolbox->setFont(font1);
        targetPage = new QWidget();
        targetPage->setObjectName(QString::fromUtf8("targetPage"));
        targetPage->setGeometry(QRect(0, 0, 421, 274));
        targetGroup = new QGroupBox(targetPage);
        targetGroup->setObjectName(QString::fromUtf8("targetGroup"));
        targetGroup->setGeometry(QRect(10, 0, 401, 281));
        layoutWidget1 = new QWidget(targetGroup);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 20, 391, 241));
        verticalLayout_3 = new QVBoxLayout(layoutWidget1);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label = new QLabel(layoutWidget1);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        horizontalLayout_5->addWidget(label);

        thickness = new QDoubleSpinBox(layoutWidget1);
        thickness->setObjectName(QString::fromUtf8("thickness"));
        thickness->setMaximumSize(QSize(100, 16777215));
        thickness->setDecimals(5);
        thickness->setMinimum(0);
        thickness->setMaximum(1e+09);
        thickness->setValue(0);

        horizontalLayout_5->addWidget(thickness);

        thicknessError = new QDoubleSpinBox(layoutWidget1);
        thicknessError->setObjectName(QString::fromUtf8("thicknessError"));
        thicknessError->setMaximumSize(QSize(100, 16777215));
        thicknessError->setDecimals(5);
        thicknessError->setMaximum(1e+09);

        horizontalLayout_5->addWidget(thicknessError);


        verticalLayout_3->addLayout(horizontalLayout_5);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        label_4 = new QLabel(layoutWidget1);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setAlignment(Qt::AlignCenter);

        horizontalLayout_8->addWidget(label_4);

        halflife = new QDoubleSpinBox(layoutWidget1);
        halflife->setObjectName(QString::fromUtf8("halflife"));
        halflife->setMaximumSize(QSize(100, 16777215));
        halflife->setDecimals(5);
        halflife->setMaximum(1e+09);

        horizontalLayout_8->addWidget(halflife);

        halflifeError = new QDoubleSpinBox(layoutWidget1);
        halflifeError->setObjectName(QString::fromUtf8("halflifeError"));
        halflifeError->setMaximumSize(QSize(100, 16777215));
        halflifeError->setDecimals(5);
        halflifeError->setMaximum(1e+09);

        horizontalLayout_8->addWidget(halflifeError);


        verticalLayout_3->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        label_5 = new QLabel(layoutWidget1);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setFont(font1);
        label_5->setAlignment(Qt::AlignCenter);

        horizontalLayout_9->addWidget(label_5);

        tm = new QDoubleSpinBox(layoutWidget1);
        tm->setObjectName(QString::fromUtf8("tm"));
        tm->setMaximumSize(QSize(100, 16777215));
        tm->setDecimals(5);
        tm->setMaximum(1e+09);

        horizontalLayout_9->addWidget(tm);

        tmError = new QDoubleSpinBox(layoutWidget1);
        tmError->setObjectName(QString::fromUtf8("tmError"));
        tmError->setMaximumSize(QSize(100, 16777215));
        tmError->setDecimals(5);
        tmError->setMaximum(1e+09);

        horizontalLayout_9->addWidget(tmError);


        verticalLayout_3->addLayout(horizontalLayout_9);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        label_6 = new QLabel(layoutWidget1);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setAlignment(Qt::AlignCenter);

        horizontalLayout_10->addWidget(label_6);

        tw = new QDoubleSpinBox(layoutWidget1);
        tw->setObjectName(QString::fromUtf8("tw"));
        tw->setMaximumSize(QSize(100, 16777215));
        tw->setDecimals(5);
        tw->setMaximum(1e+09);

        horizontalLayout_10->addWidget(tw);

        twError = new QDoubleSpinBox(layoutWidget1);
        twError->setObjectName(QString::fromUtf8("twError"));
        twError->setMaximumSize(QSize(100, 16777215));
        twError->setDecimals(5);
        twError->setMaximum(1e+09);

        horizontalLayout_10->addWidget(twError);


        verticalLayout_3->addLayout(horizontalLayout_10);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        label_7 = new QLabel(layoutWidget1);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setAlignment(Qt::AlignCenter);

        horizontalLayout_11->addWidget(label_7);

        reltd = new QDoubleSpinBox(layoutWidget1);
        reltd->setObjectName(QString::fromUtf8("reltd"));
        reltd->setMaximumSize(QSize(100, 16777215));
        reltd->setDecimals(5);
        reltd->setMaximum(1);

        horizontalLayout_11->addWidget(reltd);

        reltdError = new QDoubleSpinBox(layoutWidget1);
        reltdError->setObjectName(QString::fromUtf8("reltdError"));
        reltdError->setMaximumSize(QSize(100, 16777215));
        reltdError->setDecimals(5);
        reltdError->setMaximum(1);

        horizontalLayout_11->addWidget(reltdError);


        verticalLayout_3->addLayout(horizontalLayout_11);

        inputToolbox->addItem(targetPage, QString::fromUtf8("Target && Measurement"));
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        page_2->setGeometry(QRect(0, 0, 421, 274));
        inputGroup = new QGroupBox(page_2);
        inputGroup->setObjectName(QString::fromUtf8("inputGroup"));
        inputGroup->setGeometry(QRect(20, 10, 521, 261));
        inputBox = new QTextEdit(inputGroup);
        inputBox->setObjectName(QString::fromUtf8("inputBox"));
        inputBox->setGeometry(QRect(0, 70, 371, 171));
        inputBox->setFont(font2);
        inputBox->setStyleSheet(QString::fromUtf8("font: 9pt \"Courier 10 Pitch\";"));
        label_8 = new QLabel(inputGroup);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(0, 40, 361, 20));
        label_8->setAlignment(Qt::AlignCenter);
        inputToolbox->addItem(page_2, QString::fromUtf8("Energy/Efficiency/Intensity/Counts"));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        page->setGeometry(QRect(0, 0, 421, 274));
        currentGroup = new QGroupBox(page);
        currentGroup->setObjectName(QString::fromUtf8("currentGroup"));
        currentGroup->setGeometry(QRect(20, 10, 391, 211));
        currentPath = new QLineEdit(currentGroup);
        currentPath->setObjectName(QString::fromUtf8("currentPath"));
        currentPath->setGeometry(QRect(20, 30, 251, 31));
        browseButton = new QPushButton(currentGroup);
        browseButton->setObjectName(QString::fromUtf8("browseButton"));
        browseButton->setGeometry(QRect(290, 30, 90, 27));
        label_9 = new QLabel(currentGroup);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(70, 70, 311, 121));
        inputToolbox->addItem(page, QString::fromUtf8("Current"));
        layoutWidget2 = new QWidget(crossTab);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(20, 380, 801, 51));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(318, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        calButton = new QPushButton(layoutWidget2);
        calButton->setObjectName(QString::fromUtf8("calButton"));
        QFont font3;
        font3.setPointSize(12);
        calButton->setFont(font3);

        horizontalLayout_3->addWidget(calButton);

        currentButton = new QPushButton(layoutWidget2);
        currentButton->setObjectName(QString::fromUtf8("currentButton"));

        horizontalLayout_3->addWidget(currentButton);

        nprodButton = new QPushButton(layoutWidget2);
        nprodButton->setObjectName(QString::fromUtf8("nprodButton"));
        nprodButton->setEnabled(false);

        horizontalLayout_3->addWidget(nprodButton);

        closeButton = new QPushButton(layoutWidget2);
        closeButton->setObjectName(QString::fromUtf8("closeButton"));

        horizontalLayout_3->addWidget(closeButton);

        horizontalSpacer_2 = new QSpacerItem(298, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        tabWidget_2->addTab(crossTab, QString());
        effTab = new QWidget();
        effTab->setObjectName(QString::fromUtf8("effTab"));
        eff_inputTable = new QTableWidget(effTab);
        if (eff_inputTable->columnCount() < 6)
            eff_inputTable->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        eff_inputTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        eff_inputTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        eff_inputTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        eff_inputTable->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        eff_inputTable->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        eff_inputTable->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        if (eff_inputTable->rowCount() < 100)
            eff_inputTable->setRowCount(100);
        eff_inputTable->setObjectName(QString::fromUtf8("eff_inputTable"));
        eff_inputTable->setGeometry(QRect(220, 220, 611, 281));
        eff_inputTable->setGridStyle(Qt::DotLine);
        eff_inputTable->setRowCount(100);
        eff_sourceTable = new QTableWidget(effTab);
        if (eff_sourceTable->columnCount() < 6)
            eff_sourceTable->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        eff_sourceTable->setHorizontalHeaderItem(0, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        eff_sourceTable->setHorizontalHeaderItem(1, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        eff_sourceTable->setHorizontalHeaderItem(2, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        eff_sourceTable->setHorizontalHeaderItem(3, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        eff_sourceTable->setHorizontalHeaderItem(4, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        eff_sourceTable->setHorizontalHeaderItem(5, __qtablewidgetitem11);
        if (eff_sourceTable->rowCount() < 5)
            eff_sourceTable->setRowCount(5);
        eff_sourceTable->setObjectName(QString::fromUtf8("eff_sourceTable"));
        eff_sourceTable->setGeometry(QRect(220, 10, 611, 201));
        eff_sourceTable->setGridStyle(Qt::DotLine);
        eff_sourceTable->setRowCount(5);
        layoutWidget3 = new QWidget(effTab);
        layoutWidget3->setObjectName(QString::fromUtf8("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(10, 10, 201, 81));
        gridLayout = new QGridLayout(layoutWidget3);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        detLabel = new QLabel(layoutWidget3);
        detLabel->setObjectName(QString::fromUtf8("detLabel"));

        gridLayout->addWidget(detLabel, 0, 0, 1, 1);

        eff_detCombo = new QComboBox(layoutWidget3);
        eff_detCombo->setObjectName(QString::fromUtf8("eff_detCombo"));

        gridLayout->addWidget(eff_detCombo, 0, 1, 1, 1);

        eff_geomLabel = new QLabel(layoutWidget3);
        eff_geomLabel->setObjectName(QString::fromUtf8("eff_geomLabel"));

        gridLayout->addWidget(eff_geomLabel, 1, 0, 1, 1);

        eff_geomBox = new QDoubleSpinBox(layoutWidget3);
        eff_geomBox->setObjectName(QString::fromUtf8("eff_geomBox"));

        gridLayout->addWidget(eff_geomBox, 1, 1, 1, 1);

        eff_calButton = new QPushButton(effTab);
        eff_calButton->setObjectName(QString::fromUtf8("eff_calButton"));
        eff_calButton->setGeometry(QRect(30, 460, 151, 31));
        tabWidget_2->addTab(effTab, QString());
        bamWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(bamWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 853, 24));
        QFont font4;
        font4.setPointSize(11);
        menuBar->setFont(font4);
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        menuHelp->setEnabled(false);
        menu_File = new QMenu(menuBar);
        menu_File->setObjectName(QString::fromUtf8("menu_File"));
        menu_File->setEnabled(true);
        bamWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(bamWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        bamWindow->setStatusBar(statusBar);

        menuBar->addAction(menu_File->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuHelp->addAction(actionAbout);
        menu_File->addAction(actionLoad);
        menu_File->addAction(actionSave);

        retranslateUi(bamWindow);

        tabWidget_2->setCurrentIndex(0);
        resultToolbox->setCurrentIndex(2);
        tabWidget->setCurrentIndex(0);
        inputToolbox->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(bamWindow);
    } // setupUi

    void retranslateUi(QMainWindow *bamWindow)
    {
        bamWindow->setWindowTitle(QApplication::translate("bamWindow", "myBAM!", 0, QApplication::UnicodeUTF8));
        actionLoad->setText(QApplication::translate("bamWindow", "Load", 0, QApplication::UnicodeUTF8));
        actionSave->setText(QApplication::translate("bamWindow", "Save As", 0, QApplication::UnicodeUTF8));
        actionSave->setShortcut(QString());
        actionAbout->setText(QApplication::translate("bamWindow", "About", 0, QApplication::UnicodeUTF8));
        resultsGroup->setTitle(QApplication::translate("bamWindow", "Results", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("bamWindow", "Gammalinie          Crossection (cm\302\262)          Fehler (cm\302\262)", 0, QApplication::UnicodeUTF8));
        resultToolbox->setItemText(resultToolbox->indexOf(page_3), QApplication::translate("bamWindow", "Crosssections", 0, QApplication::UnicodeUTF8));
        resultToolbox->setItemText(resultToolbox->indexOf(page_4), QApplication::translate("bamWindow", "Current Plot", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_1), QApplication::translate("bamWindow", "N(t)", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("bamWindow", "dN(t)", 0, QApplication::UnicodeUTF8));
        resultToolbox->setItemText(resultToolbox->indexOf(page_5), QApplication::translate("bamWindow", "Produced Nuclei Plot", 0, QApplication::UnicodeUTF8));
        targetGroup->setTitle(QApplication::translate("bamWindow", "Target && Measurement", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("bamWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Arial'; font-size:8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">N</span><span style=\" font-size:12pt; vertical-align:sub;\">Target  </span><span style=\" font-size:12pt;\">/ 10</span><span style=\" font-size:12pt; vertical-align:super;\">15</span><span style=\" font-size:12pt;\"> cm</span><span style=\" font-size:12pt; vertical-align:super;\">2</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        thickness->setPrefix(QString());
        label_4->setText(QApplication::translate("bamWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Arial'; font-size:8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">Half-life [s]</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("bamWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Arial'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">T</span><span style=\" font-size:12pt; vertical-align:sub;\">Counting</span><span style=\" font-size:12pt;\"> [s]</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("bamWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Arial'; font-size:8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">T</span><span style=\" font-size:12pt; vertical-align:sub;\">waiting</span><span style=\" font-size:12pt;\"> [s]</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("bamWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Arial'; font-size:8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">relative T</span><span style=\" font-size:12pt; vertical-align:sub;\">live</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        inputToolbox->setItemText(inputToolbox->indexOf(targetPage), QApplication::translate("bamWindow", "Target && Measurement", 0, QApplication::UnicodeUTF8));
        inputGroup->setTitle(QApplication::translate("bamWindow", "Energy/Efficieny/Intensity", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("bamWindow", "Energie(keV)       Intensit\303\244t       dI       Effizienz       dEff       Counts       dC", 0, QApplication::UnicodeUTF8));
        inputToolbox->setItemText(inputToolbox->indexOf(page_2), QApplication::translate("bamWindow", "Energy/Efficiency/Intensity/Counts", 0, QApplication::UnicodeUTF8));
        currentGroup->setTitle(QApplication::translate("bamWindow", "Current", 0, QApplication::UnicodeUTF8));
        browseButton->setText(QApplication::translate("bamWindow", "Browse", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("bamWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Arial'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:11pt; font-weight:600;\">Please notice:</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">The current file should be in a form where the first</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">column should hold the elapsed time during the </p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">activation "
                        "and the second column should hold the </p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">accumulated beam particles.</p></body></html>", 0, QApplication::UnicodeUTF8));
        inputToolbox->setItemText(inputToolbox->indexOf(page), QApplication::translate("bamWindow", "Current", 0, QApplication::UnicodeUTF8));
        calButton->setText(QApplication::translate("bamWindow", "Calculate", 0, QApplication::UnicodeUTF8));
        currentButton->setText(QApplication::translate("bamWindow", "Plot Current", 0, QApplication::UnicodeUTF8));
        nprodButton->setText(QApplication::translate("bamWindow", "Plot NProd", 0, QApplication::UnicodeUTF8));
        closeButton->setText(QApplication::translate("bamWindow", "Close", 0, QApplication::UnicodeUTF8));
        tabWidget_2->setTabText(tabWidget_2->indexOf(crossTab), QApplication::translate("bamWindow", "Total Cross Sections", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = eff_inputTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("bamWindow", "Energy [keV]", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = eff_inputTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("bamWindow", "d(Energy) [keV]", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = eff_inputTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("bamWindow", "Intensity", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem3 = eff_inputTable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("bamWindow", "d(Intensity)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem4 = eff_inputTable->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("bamWindow", "Peak Counts", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem5 = eff_inputTable->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("bamWindow", "d(PeakCounts)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem6 = eff_sourceTable->horizontalHeaderItem(0);
        ___qtablewidgetitem6->setText(QApplication::translate("bamWindow", "Source", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem7 = eff_sourceTable->horizontalHeaderItem(1);
        ___qtablewidgetitem7->setText(QApplication::translate("bamWindow", "Activity [Bq]", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem8 = eff_sourceTable->horizontalHeaderItem(2);
        ___qtablewidgetitem8->setText(QApplication::translate("bamWindow", "d(Activity) [Bq]", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem9 = eff_sourceTable->horizontalHeaderItem(3);
        ___qtablewidgetitem9->setText(QApplication::translate("bamWindow", "Date", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem10 = eff_sourceTable->horizontalHeaderItem(4);
        ___qtablewidgetitem10->setText(QApplication::translate("bamWindow", "rel. Livetime", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem11 = eff_sourceTable->horizontalHeaderItem(5);
        ___qtablewidgetitem11->setText(QApplication::translate("bamWindow", "Runtime [s]", 0, QApplication::UnicodeUTF8));
        detLabel->setText(QApplication::translate("bamWindow", "Detector:", 0, QApplication::UnicodeUTF8));
        eff_detCombo->clear();
        eff_detCombo->insertItems(0, QStringList()
         << QApplication::translate("bamWindow", "CloZi A0", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("bamWindow", "CloZi A1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("bamWindow", "CloZi A2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("bamWindow", "CloZi A3", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("bamWindow", "CloZi B0", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("bamWindow", "CloZi B1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("bamWindow", "CloZi B2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("bamWindow", "CloZi B3", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("bamWindow", "CloZi SUM", 0, QApplication::UnicodeUTF8)
        );
        eff_geomLabel->setText(QApplication::translate("bamWindow", "geometry factor:", 0, QApplication::UnicodeUTF8));
        eff_calButton->setText(QApplication::translate("bamWindow", "Calculate", 0, QApplication::UnicodeUTF8));
        tabWidget_2->setTabText(tabWidget_2->indexOf(effTab), QApplication::translate("bamWindow", "Clover Efficiency", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("bamWindow", "&Help", 0, QApplication::UnicodeUTF8));
        menu_File->setTitle(QApplication::translate("bamWindow", "&File", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class bamWindow: public Ui_bamWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BAMWINDOW_H

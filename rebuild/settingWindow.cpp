#include"settingWindow.h"

SettingWindow::SettingWindow(QWidget *parent,QSettings *oldSetting) : QDialog(parent){
    localSetting = oldSetting;
    createWindow();
    createLayout();
    connect(OK,SIGNAL(clicked()),this,SLOT(Change()));
    connect(Cancle,SIGNAL(clicked()),this,SLOT(reject()));
}

SettingWindow::~SettingWindow()
{
	delete layout1;
	delete chartRange;
	delete timeRange;
	delete timeUnit;
	delete layout2;
	delete dataNum;
	delete numSlider;
	delete layout3;
	delete serialPort;
	delete layout4;
	delete database;
	delete hostname;
	delete username;
	delete passwd;
	delete databasename;
	delete layout5;
	delete OK;
	delete Cancle;
	delete mainLayout;
    delete layout10;
    delete clarmBox;
    delete clarmLabel;
}

void SettingWindow::createWindow(){

    this -> setWindowTitle("Settings");
    chartRange = new QLabel(this);
    chartRange -> setText(tr("图表x轴范围"));
    timeRange = new QSpinBox(this);
    timeRange->setRange(1,60);
    timeRange -> setValue(localSetting -> value("chartRange",QVariant(60)).toInt());
    timeUnit = new QComboBox(this);
    timeUnit->addItem("second(s)");
    timeUnit->addItem("minute(s)");
    timeUnit->addItem("hour(s)");
    timeUnit ->  setCurrentText(localSetting -> value("timeUnit",QVariant("minute(s)")).toString());

    dataNum = new QLabel (this);
    dataNum -> setText(tr("本地数据数量"));
    numSlider = new QSpinBox(this);
    numSlider -> setRange(2,1000);
    numSlider -> setValue(localSetting -> value("dataNum",QVariant(100)).toInt());

    serialName = new QLabel(this);
    serialName -> setText(tr("串口"));
    serialPort = new QComboBox (this);
    const auto infos = QSerialPortInfo::availablePorts();
    for(auto i : infos)
    {
        serialPort->addItem(i.portName());
    }
    serialPort  -> setCurrentIndex(localSetting->value("serialName",QVariant(0)).toInt());

    clarmLabel = new QLabel (this);
    clarmLabel -> setText(tr("警报温度"));
    clarmBox = new QSpinBox(this);
    clarmBox -> setRange(0,1000);
    clarmBox -> setValue(localSetting -> value("clarmTemper",QVariant(50)).toInt());

    database     = new QLabel(this);
    database     ->setText(tr("数据库设置"));
    host 	     = new QLabel(this);
    host	     -> setText(tr("主机名"));
    hostname     = new QLineEdit(this);
    hostname    ->  setText(localSetting-> value("hostName",QVariant("47.93.191.3")).toString());
    user	     = new QLabel(this);
    user	     -> setText(tr("用户名"));
    username     = new QLineEdit(this);
    username -> setText(localSetting -> value("userName",QVariant("public")).toString());
    pass 	     = new QLabel(this);
    pass         -> setText(tr("密码"));
    passwd       = new QLineEdit(this);
    passwd -> setText(localSetting -> value("passWord",QVariant("123456")).toString());
    dataname     = new QLabel(this);
    dataname     -> setText(tr("库名"));
    databasename = new QLineEdit(this);
    databasename -> setText(localSetting -> value("databaseName",QVariant("temperature")).toString());



    OK = new QPushButton(this);
    Cancle = new QPushButton(this);
    OK -> setText(tr("确定"));
    Cancle -> setText(tr("取消"));

}

void SettingWindow::createLayout(){
    layout1 = new QHBoxLayout;
	layout1 -> addWidget(chartRange);
	layout1 -> addWidget(timeRange);
	layout1 -> addWidget(timeUnit);

	layout2 = new QHBoxLayout;
	layout2 -> addWidget(dataNum);
	layout2 -> addWidget(numSlider);

	layout3 = new QHBoxLayout;
	layout3 -> addWidget(serialName);
	layout3 -> addWidget(serialPort);

	layout6 = new QHBoxLayout;
	layout6 ->addWidget(host);
	layout6 -> addWidget(hostname);

	layout7 = new QHBoxLayout;
	layout7 -> addWidget(user);
	layout7 -> addWidget(username);

	layout8 = new QHBoxLayout;
	layout8 -> addWidget(pass);
	layout8 -> addWidget(passwd);

	layout9 = new QHBoxLayout;
	layout9 -> addWidget(dataname);
	layout9 -> addWidget(databasename);


	layout4 = new QVBoxLayout;
	layout4 -> addWidget(database);
	layout4 -> addLayout(layout6);
	layout4 -> addLayout(layout7);
	layout4 -> addLayout(layout8);
	layout4 -> addLayout(layout9);

	layout5 = new QHBoxLayout;
	layout5 -> addWidget(OK);
	layout5 -> addWidget(Cancle);

    layout10 = new QHBoxLayout;
    layout10 -> addWidget(clarmLabel);
    layout10 -> addWidget(clarmBox);

	mainLayout = new QVBoxLayout;
	mainLayout -> addLayout(layout1);
	mainLayout -> addStretch();
	mainLayout -> addLayout(layout2);
    mainLayout -> addStretch();
    mainLayout -> addLayout(layout10);
	mainLayout -> addStretch();
	mainLayout -> addLayout(layout3);
	mainLayout -> addStretch();
	mainLayout -> addLayout(layout4);
	mainLayout -> addStretch();
	mainLayout -> addLayout(layout5);
	mainLayout -> setSpacing(20);
	layout4    -> setSpacing(10);

	this -> setLayout(mainLayout);

}

void SettingWindow::Change()
{
	localSetting -> setValue("chartRange",timeRange->value());                       //设置1：表格范围
	localSetting -> setValue("timeUnit",timeUnit -> currentText());                        //设置2：表格范围的单位
	localSetting -> setValue("dataNum",numSlider -> value());                        //设置3：本地保存数据个数
	localSetting -> setValue("serialName",serialPort -> currentIndex());		//设置4：串口名
	localSetting -> setValue("hostName",hostname -> text());  			//设置5:主机名
	localSetting -> setValue("userName",username -> text());                         //设置6：用户名
	localSetting -> setValue("passWord",passwd -> text()); 				//设置6:密码
	localSetting -> setValue("databaseName",databasename -> text());			//设置7:数据库名
    localSetting -> setValue("clarmTemper",clarmBox-> value());
    QMessageBox::warning(this,tr("Warning"),tr("Restart to take effect"),QMessageBox::Ok);
	this -> accept();
}

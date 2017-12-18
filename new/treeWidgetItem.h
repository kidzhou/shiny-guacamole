#include<QTreeWidgetItem>
#include<QLineSeries>
#include<QStringList>
using namespace QtCharts;
class treeWidgetItem:public QObject, public QTreeWidgetItem{
  Q_OBJECT
public slots:
  void setData(QLineSeries *data);
public:
  treeWidgetItem(QStringList list);
  QLineSeries *data();
private:
  QLineSeries *Data=nullptr;
};

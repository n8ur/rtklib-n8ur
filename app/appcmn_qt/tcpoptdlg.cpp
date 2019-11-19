//---------------------------------------------------------------------------
// ported to Qt by Jens Reimann

#include <stdio.h>

#include <QShowEvent>
#include <QProcess>
#include <QIntValidator>
#include <QUrl>

#include "rtklib.h"
#include "tcpoptdlg.h"

//---------------------------------------------------------------------------

#define NTRIP_TIMEOUT   10000                           // response timeout (ms)
#define NTRIP_CYCLE             50                      // processing cycle (ms)
#define MAXSRCTBL               512000                  // max source table size (bytes)
#define ENDSRCTBL               "ENDSOURCETABLE"        // end marker of table
#define MAXLINE                 1024                    // max line size (byte)

//---------------------------------------------------------------------------
TcpOptDialog::TcpOptDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    connect(BtnOk, SIGNAL(clicked(bool)), this, SLOT(BtnOkClick()));
    connect(BtnNtrip, SIGNAL(clicked(bool)), this, SLOT(BtnNtripClick()));
    connect(BtnCancel, SIGNAL(clicked(bool)), this, SLOT(reject()));
}
//---------------------------------------------------------------------------
void TcpOptDialog::showEvent(QShowEvent *event)
{
    QString ti[] = { tr("TCP Server Options "),  tr("TCP Client Options"),
             tr("NTRIP Server Options"), tr("NTRIP Client Options"),
                "NTRIP Caster Client Options",
                "NTRIP Caster Server Options", "UDP Server Options",
                "UDP Client Options"};

    if (event->spontaneous()) return;

    Addr->clear();
    MntPnt->clear();

    for (int i = 0; i < MAXHIST; i++)
        if (History[i] != "") Addr->addItem(History[i]);
    for (int i = 0; i < MAXHIST; i++)
        if (MntpHist[i] != "") MntPnt->addItem(MntpHist[i]);

    int index = Path.lastIndexOf("@");

    QStringList tokens= Path.mid(0,index).split(':'); // separate user and password
    if (tokens.size() == 2)
    {
        User->setText(tokens.at(0));
        Passwd->setText(tokens.at(1));
    } else if (tokens.size() == 1)
        User->setText(tokens.at(0));

    QString url_str = Path.mid(index); // use the rest

    index = url_str.lastIndexOf(":"); // separate "str"
    Str->setText(url_str.mid(index + 1));

    QUrl url(QString("ftp://") + url_str.mid(0,index));

    Addr->insertItem(0, url.host()); Addr->setCurrentText(url.host());
    Port->setValue(url.port());
    MntPnt->insertItem(0, url.path().mid(1)); MntPnt->setCurrentText(url.path().mid(1));

    Addr->setEnabled((Opt >= 1 && Opt <= 3) || Opt == 7);
    MntPnt->setEnabled(Opt >= 2 && Opt <= 4);
    User->setEnabled(Opt >= 3 && Opt <= 4);
    Passwd->setEnabled(Opt >= 2 && Opt <= 5);
    Str->setEnabled(Opt == 2);
    LabelAddr->setText(Opt >= 2 && Opt <= 5 ? tr("NTRIP Caster Host") : tr("Server Address"));
    LabelAddr->setEnabled((Opt >= 1 && Opt <= 3) || Opt == 7);
    LabelMntPnt->setEnabled(Opt >= 2 && Opt <= 4);
    LabelUser->setEnabled(Opt >= 3 && Opt <= 4);
    LabelPasswd->setEnabled(Opt >= 2 && Opt <= 5);
    LabelStr->setEnabled(Opt == 2);

    setWindowTitle(ti[Opt]);

    BtnNtrip->setVisible(Opt == 2 || Opt == 3);
}
//---------------------------------------------------------------------------
void TcpOptDialog::BtnOkClick()
{
    QString User_Text = User->text(), Passwd_Text = Passwd->text();
    QString Addr_Text = Addr->currentText(), Port_Text = Port->text();
    QString MntPnt_Text = MntPnt->currentText(), Str_Text = Str->text();

    Path = QString("%1:%2@%3:%4/%5:%6").arg(User_Text).arg(Passwd_Text)
           .arg(Addr_Text).arg(Port_Text).arg(MntPnt_Text)
           .arg(Str_Text);

    AddHist(Addr, History);
    AddHist(MntPnt, MntpHist);

    accept();
}
//---------------------------------------------------------------------------
void TcpOptDialog::AddHist(QComboBox *list, QString *hist)
{
    for (int i = 0; i < MAXHIST; i++) {
        if (list->currentText() != hist[i]) continue;
        for (int j = i + 1; j < MAXHIST; j++) hist[j - 1] = hist[j];
        hist[MAXHIST - 1] = "";
	}
    for (int i = MAXHIST - 1; i > 0; i--) hist[i] = hist[i - 1];
    hist[0] = list->currentText();

    list->clear();
    for (int i = 0; i < MAXHIST; i++)
        if (hist[i] != "") list->addItem(hist[i]);
}
//---------------------------------------------------------------------------
void TcpOptDialog::BtnNtripClick()
{
    QString Addr_Text = Addr->currentText();
    QString Port_Text = Port->text();

    ExecCmd("srctblbrows_qt " + Addr_Text + ":" + Port_Text, 1);
}
//---------------------------------------------------------------------------
int TcpOptDialog::ExecCmd(QString cmd, int show)
{
    QProcess prog;

    Q_UNUSED(show);

    prog.start(cmd); /* FIXME: show option not yet supported */
    return 1;
}
//---------------------------------------------------------------------------

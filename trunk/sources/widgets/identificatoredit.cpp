#include "identificatoredit.h"

/*!\func
 * constructor
 * \params
 * - parent - parent object
 * \return no
 */
IdentificatorEdit::IdentificatorEdit(QWidget *parent) :
    QLineEdit(parent)
{
    oldText = "empty_" + QString::number(qrand());
    connect(this, SIGNAL(textEdited(QString)), this, SLOT(textEdited(QString)));
}
/*!\func
 * return type of the node
 * \params
 * - text - text after change
 * \return no
 */
void IdentificatorEdit::textEdited ( const QString & text )
{
	//QString latin("QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm"),
	//cyrilic("ÉÖÓÊÅÍÃØÙÇÕÚÔÛÂÀÏĞÎËÄÆİß×ÑÌÈÒÜÁŞéöóêåíãøùçõúôûâàïğîëäæıÿ÷ñìèòüáş"),
	//signs("._-=+*/()[]{}<>!?"), digits("1234567890");
	//QString valid(latin + cyrilic + signs);
	if(text.isEmpty())
	{
	}
	else
	{
		/*for(int i = 0; i < text.length(); i++)
			if(!valid.contains(text[i])&&!digits.contains(text[i]))
			{
				setText(oldText);
				return;
			}*/
			oldText = text.left(32);
	}
	if(oldText != text)
		setText(oldText);
}

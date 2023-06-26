#include <Ice/Ice.h>
#include <dictionary.h>

using namespace std;
using namespace DictonaryIceModule; // mapped from ICE module name

int main(int argc, char *argv[])
{
    int status = 0;
    Ice::CommunicatorPtr ic;
    try
    {
        ic = Ice::initialize(argc, argv);
        Ice::ObjectPrx base = ic->stringToProxy("MyIceServiceName:default -p 10000");
        TranslatorPrx trans = TranslatorPrx::checkedCast(base);
        if (!trans)
            throw "invalid proxy";

        string s;
        while (1)
        {
            try
            {
                cout << "enter word to translate: ";
                cin >> s;
                words results = trans->translate(s);
                for (string word : results)
                {
                    cout << word << endl;
                }
            }
            catch (NoSuchWordException ex)
            {
                cout << "Word not found. Please try again" << endl;
            }
        }
    }
    catch (const Ice::Exception &ex)
    {
        cerr << ex << endl;
        status = 1;
    }
    catch (const char *msg)
    {
        cerr << msg << endl;
        status = 1;
    }
    return status;
}
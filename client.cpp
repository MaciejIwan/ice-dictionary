#include <Ice/Ice.h>
#include <dictionary.h>

using namespace std;
using namespace DictionaryModule;

int main(int argc, char *argv[])
{
    int status;
    Ice::CommunicatorPtr ic;

    try
    {
        ic = Ice::initialize(argc, argv);
        Ice::ObjectPrx base = ic->stringToProxy("serviceName:default -p 10000");
        translatorPrx t = translatorPrx::checkedCast(base);
         if (!t)
            throw "can't connect";
        

        string s;

        while(1){
            try {
                cout << "Word to translate: ";
            cin >> s;
            words response = t->translate(s);
            
            cout << "Found translations: " << endl;
            for (string word : response)
                cout << word << endl;
            } catch (NoSuchWord e){
                cout << "Word no found" << endl;
            }
            
        }
       

        
    }
    catch (const Ice::Exception &ex)
    {
        cerr << ex << endl;
        status = 1;
    }

    if (ic)
        ic->destroy();

    return status;
}

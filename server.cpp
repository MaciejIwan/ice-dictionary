#include <Ice/Ice.h>
#include <dictionary.h>

using namespace std;
using namespace DictonaryIceModule;

myDictionary dictionary;

class TranslatorImpl : public Translator
{
public:
    virtual words translate(const string &s, const Ice::Current &);
};

words TranslatorImpl::translate(const string &s, const Ice::Current &)
{
    words response = dictionary[s];
    if(response.size() == 0)
        throw NoSuchWordException();
    return response;
}

void initTestDictionary(){
    words someTranslations;
    someTranslations.push_back("hello");
    someTranslations.push_back("hi");
    dictionary["hej"] = someTranslations;
}
int main(int argc, char *argv[])
{
    initTestDictionary();
    int status = 0;
    Ice::CommunicatorPtr ic;

    try
    {
        ic = Ice::initialize(argc, argv);
        Ice::ObjectAdapterPtr adapter = ic->createObjectAdapterWithEndpoints(
            "MyAdapter", "default -p 10000");
        Ice::ObjectPtr object = new TranslatorImpl;
        adapter->add(object, Ice::stringToIdentity("MyIceServiceName"));
        adapter->activate();
        ic->waitForShutdown();
    }
    catch (const Ice::Exception &e)
    {
        cerr << e << endl;
        status = 1;
    }
    catch (const char *msg)
    {
        cerr << msg << endl;
        status = 1;
    }

    return status;
}
#include <Ice/Ice.h>
#include <dictionary.h>

using namespace std;
using namespace DictionaryModule;

myDictionary dict;

class TranslatorImpl : public translator {
    virtual words translate(const string &s, const Ice::Current&);
};

words TranslatorImpl::translate(const string&s, const Ice::Current&){
    words res = dict[s];
    if(res.size() == 0)
        throw NoSuchWord();
    return res;
}



void init_data(){
    words temp;
    temp.push_back("hello");
    temp.push_back("hi");

    dict["hej"] = temp;
}

int main(int argc, char *argv[])
{
    init_data();
    int status;
    Ice::CommunicatorPtr ic;
    Ice::ObjectAdapterPtr adapter;
    try {
        ic = Ice::initialize(argc, argv);
        adapter = ic->createObjectAdapterWithEndpoints("MyAdapter", "default -p 10000");
        Ice::ObjectPtr object = new TranslatorImpl;
        adapter->add(object, Ice::stringToIdentity("serviceName"));
        adapter->activate();
        ic->waitForShutdown();
    } catch (const Ice::Exception &ex) {
        cerr << ex << endl;
        status = 1;
    }

    if(ic)
        ic->destroy();
    if(adapter)
        ic->destroy();

    return status;
}

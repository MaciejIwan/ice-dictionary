module DictionaryModule {
    exception NoSuchWord {};
    sequence<string> words;
    dictionary<string, words> myDictionary;

    interface translator {
        words translate(string s) throws NoSuchWord;
    };
};
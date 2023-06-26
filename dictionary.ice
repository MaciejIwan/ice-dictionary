module DictonaryIceModule {
    exception NoSuchWordException {};

    sequence<string> words;
    dictionary<string, words> myDictionary;

    interface Translator {
        words translate(string word) throws NoSuchWordException;
    };
};
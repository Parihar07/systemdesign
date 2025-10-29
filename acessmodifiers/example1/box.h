class Box{
    private: 
    int len;
    public:
        int getlength() const {
            // len = 10; //we cannot do this as we siad this function is const will not manipulate the values in the class
            return len;
        };
};
//
//  function.hpp
//  encoding and decoding
//
//  Created by 朱季葳 on 2021/5/17.
//




#include <stdio.h>
#include <iostream>
#include <string>

class Codec {
public:
    virtual void encode() = 0;
    virtual void decode() = 0;
    virtual ~Codec() { } // Do nothing
    virtual void show(std::ostream& os) const = 0;
    virtual bool is_encoded() const = 0;
};

class DummyCodec: public Codec {
public:
    DummyCodec(std::string s): encoded{false}, code_str{s} { }

    void encode() {
        encoded = true;
    }

    void decode() {
        encoded = false;
    }

    void show(std::ostream& os) const {
        os << code_str;
    }

    bool is_encoded() const { return encoded; }

private:
    bool encoded;
    std::string code_str;
};

class RleCodec: public Codec
{
public:
    RleCodec(std::string s): encoded{false}, code_str{s} { }


    void encode();

    void decode();

    void show(std::ostream& os) const {
        os << code_str;
    }

    bool is_encoded() const { return encoded; }


private:
    bool encoded;
    std::string code_str;
};


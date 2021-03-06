#pragma once

#include <string>
#include "common/deftypes.h"

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 128
#endif

#define HEADER_SIZE (sizeof(OPCODE) + sizeof(framesize_t))

union BUFFER
{
    char staticBuffer[BUFFER_SIZE];
    char *dynamicBuffer;
};

struct NetworkFrame
{
    // set to the ID of the sender by network upon reception of a new message
    // the messages created by the server to be sent to the clients do not
    // use this value
    ID sender;
    framesize_t buffer_size;
    BUFFER buffer;

    NetworkFrame(const framesize_t len = BUFFER_SIZE);
    NetworkFrame(const char *buffer);
    ~NetworkFrame();

    void append(const void *bytes, const size_t len);
    void appendInt8(const int8_t i);
    void appendInt16(const int16_t i);
    void appendInt32(const int32_t i);
    void appendFloat(const float f);
    void appendString(std::string s);

    const bool dynamic() const;
    OPCODE &opcode() const;
    framesize_t &size() const;
    framesize_t totalSize() const; // including header
    char *header();
    const char *header() const;
    char *content();
    const char *content() const;

    static OPCODE &NetworkFrame::getMessageOpCode(const char *message);
    static framesize_t &getMessageSize(const char *message);
    static framesize_t getMessageTotalSize(const char *message);
    static char *getMessageHeader(char *message);
    static char *getMessageContent(char *message);
};
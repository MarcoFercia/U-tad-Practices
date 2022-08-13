#include "AudioBuffer.h"
#include <cstdio>
#include <string.h>
#include <iostream>

AudioBuffer::AudioBuffer(ALuint _iBufferID)
{
    bufferID = _iBufferID;
}

AudioBuffer::~AudioBuffer()
{
    alDeleteBuffers(1, &bufferID);
}


AudioBuffer* AudioBuffer::load(const char* filename)
{


    ALuint bufferID;
    alGenBuffers(1, &bufferID);
    if (alGetError() != AL_NO_ERROR)
    {
        printf("Error al generar buffers");
        return nullptr;
    }

    FILE* pFile = fopen(filename, "r");
    if (!pFile)
    {
        printf("No se pudo abrir el fichero");
        return nullptr;
    }


    char cBuffer[5] = "";
    fread(cBuffer, sizeof(char), 4, pFile);
    if (strcmp(cBuffer, "RIFF") != 0)
    {
        printf("No es un fichero valido");
        return nullptr;
    }


    fread(cBuffer, sizeof(char), 4, pFile);
    fread(cBuffer, sizeof(char), 4, pFile);
    fread(cBuffer, sizeof(char), 4, pFile);


    // FmtChunkSize
    fread(cBuffer, sizeof(char), 4, pFile);
    int iFmtChunkSize = cBuffer[3] << 24 | cBuffer[2] << 16 | cBuffer[1] << 8 | cBuffer[0];

    // AudioFormat
    fread(cBuffer, sizeof(char), 2, pFile);
    int iAudioFormat = cBuffer[1] << 8 | cBuffer[0];

    // Channels
    fread(cBuffer, sizeof(char), 2, pFile);
    int iChannels = cBuffer[1] << 8 | cBuffer[0];

    // SampleRate
    fread(cBuffer, sizeof(char), 4, pFile);
    ALsizei iFreq = cBuffer[3] << 24 | cBuffer[2] << 16 | cBuffer[1] << 8 | cBuffer[0];

    // ByteRate (4) + BlockAlign (2)
    fread(cBuffer, sizeof(char), 4, pFile);
    fread(cBuffer, sizeof(char), 2, pFile);


    // BitsPerSample
    fread(cBuffer, sizeof(char), 2, pFile);
    int iBitsPerSample = cBuffer[1] << 8 | cBuffer[0];

    if (iAudioFormat != 1 && iFmtChunkSize > 16)
    {
        // ExtraParamsSize
        fread(cBuffer, sizeof(char), 2, pFile);
        int iExtraParamsSize = cBuffer[1] << 8 | cBuffer[0];
        fread(cBuffer, sizeof(char), iExtraParamsSize, pFile);
    }

    bool bDataFind = false;
    while (!bDataFind)
    {
        // TODO: Intentar cambiar esto
        fread(cBuffer, sizeof(char), 1, pFile);
        if (strcmp(cBuffer, "d") == 0)
        {
            fread(cBuffer, sizeof(char), 1, pFile);
            if (strcmp(cBuffer, "a") == 0)
            {
                fread(cBuffer, sizeof(char), 1, pFile);
                if (strcmp(cBuffer, "t") == 0)
                {
                    fread(cBuffer, sizeof(char), 1, pFile);
                    if (strcmp(cBuffer, "a") == 0)
                    {
                        bDataFind = true;
                    }
                }
            }
        }
    }


    // Tamanio de los datos
    fread(cBuffer, sizeof(char), 4, pFile);
    unsigned int iDataSize = static_cast<unsigned char>(cBuffer[3]) << 24 | static_cast<unsigned char>(cBuffer[2]) << 16 | static_cast<unsigned char>(cBuffer[1]) << 8 | static_cast<unsigned char>(cBuffer[0]);
    char* pData = new char[iDataSize];
    // Datos
    fread(pData, sizeof(char), iDataSize, pFile);


    ALenum formatBuffer = AL_FORMAT_MONO8;
    if (iBitsPerSample == 8)
    {
        if (iChannels == 1)
        {
            formatBuffer = AL_FORMAT_MONO8;
        }
        else
        {
            formatBuffer = AL_FORMAT_STEREO8;
        }
    }
    else if (iBitsPerSample == 16)
    {
        if (iChannels == 1)
        {
            formatBuffer = AL_FORMAT_MONO16;
        }
        else
        {
            formatBuffer = AL_FORMAT_STEREO16;
        }
    }

    alBufferData(bufferID, formatBuffer, pData, iDataSize, iFreq);


    delete[]pData;
    fclose(pFile);

    return new AudioBuffer(bufferID);


}


uint32_t AudioBuffer::getAlBuffer() const
{
    return bufferID;
}


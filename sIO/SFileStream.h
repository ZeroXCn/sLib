#include "SFileInputStream.h"
#include "SFileOutputStream.h"
class SFileStream :protected SFileInputStream, protected SFileOutputStream
{

};
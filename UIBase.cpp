#include "UIBase.h"

UIBase::UIBase(std::string name, XMFLOAT2 pos, XMFLOAT2 size)
    : name_(name), position_(pos), size_(size) 
{
}

UIBase::~UIBase() 
{
}

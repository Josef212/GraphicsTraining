#include "PBRMaterial.h"



PBRMaterial::PBRMaterial(const char* name) : Material(name)
{
}

PBRMaterial::PBRMaterial(const char* name, Shader* sh) : Material(name, sh)
{
}


PBRMaterial::~PBRMaterial()
{
}

void PBRMaterial::OnFree()
{
}

void PBRMaterial::SendInfo(Scene * scene) const
{
}

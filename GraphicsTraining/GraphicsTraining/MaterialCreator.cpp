#include "MaterialCreator.h"

#include "ComplexMaterial.h"


MaterialCreator::MaterialCreator()
{
}


MaterialCreator::~MaterialCreator()
{
}

void MaterialCreator::OnOpen()
{
	
}

void MaterialCreator::OnClose()
{
	tmpName = "";

	for (int i = 0; i < tmpMatProperties.size(); ++i)
	{
		RELEASE(tmpMatProperties[i]);
	}

	tmpMatProperties.clear();
}

void MaterialCreator::Render()
{
}

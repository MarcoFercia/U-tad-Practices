#include "stdafx.h"
#include "Grid.h"

Grid::Grid()
{

}

Grid* Grid::Load(const char* _mapFilename, const char* _codeFilename)
{
    if (!_mapFilename || !_codeFilename)
    {
        printf("Invalid filename");
        return nullptr;
    }

    Grid* grid = new Grid();
    std::map<char, float> codeMap;

    std::ifstream codeStream;
    codeStream.open(_codeFilename);
    if (!codeStream.is_open())
    {
        printf("Error codeFile");
        codeStream.close();
        return nullptr;
    }

    std::string line1;
    while (std::getline(codeStream, line1))
    {
        const size_t index = line1.find(':');
        if (index == std::string::npos)
        {
            printf("Invalid format");
            codeStream.close();
            return nullptr;
        }
        codeMap.insert(std::make_pair(line1.at(0), std::stof(line1.substr(index + 1))));
    }
    codeStream.close();




    std::ifstream mapStream;
    mapStream.open(_mapFilename);
    if (!mapStream.is_open())
    {
        printf("Error loading map");
        mapStream.close();
        return nullptr;
    }

    std::string line2;
    int sizeX = 0;
    int sizeY = 0;
    while (std::getline(mapStream, line2))
    {
        ++sizeY;
        if (sizeX == 0)
        {
            sizeX = line2.size();
        }

        for (char it : line2)
        {
            float cost = codeMap.at(it);
            grid->mMap.push_back(cost);
        }
    }
    mapStream.close();

    grid->mSize = USVec2D(float(sizeX), float(sizeY));

    return grid;

}

float Grid::GetCost(uint32_t _index) const
{
    return mMap.at(_index);
}

float Grid::GetCost(uint32_t _row, uint32_t _col) const
{
    const uint32_t index = _row * uint32_t(mSize.mX) + _col;
    if (index > mMap.size())
    {
        return -1.f;
    }
    return GetCost(index);
}

float Grid::GetCost(const USVec2D& _gridLocation) const
{
    return GetCost(uint32_t(_gridLocation.mY), uint32_t(_gridLocation.mX));
}

USVec2D Grid::GetSize() const
{
    return mSize;
}

USVec2D Grid::GetRectSize() const
{
    return USVec2D(float(MOAIGfxDevice::Get().GetWidth()) / mSize.mX, float(MOAIGfxDevice::Get().GetHeight()) / mSize.mY);
}

bool Grid::IsValidPos(const USVec2D _pos) const
{
    return _pos.mX >= 0.f && _pos.mX < mSize.mX&& _pos.mY >= 0.f && _pos.mY < mSize.mY;
}

USVec2D Grid::GridToWorldLocation(const USVec2D& _gridLocation) const
{
    MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();
    float halfWidth = float(gfxDevice.GetWidth()) / 2.f;
    float halfHeight = float(gfxDevice.GetHeight()) / 2.f;
    USVec2D rectSize = GetRectSize();
    USVec2D screenLocation(rectSize.mX * _gridLocation.mX, rectSize.mY * _gridLocation.mY);
    USVec2D worldLocation = screenLocation - USVec2D(halfWidth, halfHeight);
    return worldLocation;
}

USVec2D Grid::WorldToGridLocation(const USVec2D& _worldLocation) const
{
    MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();
    float halfWidth = float(gfxDevice.GetWidth()) / 2.f;
    float halfHeight = float(gfxDevice.GetHeight()) / 2.f;
    USVec2D worldLocationFromScreenCorner = _worldLocation + USVec2D(halfWidth, halfHeight);
    USVec2D rectSize = GetRectSize();
    USVec2D gridLocation(floorf(worldLocationFromScreenCorner.mX / rectSize.mX), floorf(worldLocationFromScreenCorner.mY / rectSize.mY));
    return gridLocation;
}

void Grid::DrawDebug() const
{
    MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();

    const float halfWidth = float(gfxDevice.GetWidth()) / 2.f;
    const float halfHeight = float(gfxDevice.GetHeight()) / 2.f;
    USVec2D rectSize(float(gfxDevice.GetWidth()) / mSize.mX,
        float(gfxDevice.GetHeight()) / mSize.mY);
    for (int32_t row = 0; row < static_cast<int32_t>(mSize.mY); ++row)
    {
        for (int32_t col = 0; col < int32_t(mSize.mX); ++col)
        {
            USRect rect;
            rect.mXMin = float(col) * rectSize.mX - halfWidth;
            rect.mXMax = rect.mXMin + rectSize.mX;
            rect.mYMin = float(row) * rectSize.mY - halfHeight;
            rect.mYMax = rect.mYMin + rectSize.mY;

            const int32_t cost = int32_t(GetCost(row, col));

            gfxDevice.SetPenColor(0.2f, 0.2f, 0.2f, 1.f);
            if (cost == -1)
            {
                MOAIDraw::DrawRectFill(rect);
            }
            else
            {
                gfxDevice.SetPenColor(0.75f - cost * 0.03f, 0.56f - cost * 0.01f, 0.5f - cost * 0.005, 1.f);
                MOAIDraw::DrawRectFill(rect);
                gfxDevice.SetPenColor(0.1f, 0.1f, 0.1f, 1.f);
                MOAIDraw::DrawRectOutline(rect);
            }
        }
    }
}

void Grid::DrawRectangle(const USVec2D& _gridPosition, const USVec4D& _color) const
{
    MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();
}

#pragma once

using RelativeAssetPath = std::string;

struct AssetMetadata
{
    std::string    assetName;
    std::streamoff offset;
    std::streamoff size;
};
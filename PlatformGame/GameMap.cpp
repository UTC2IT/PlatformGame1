#include "stdafx.h"
#include "GameMap.h"

void GameMap::Render()
{
	for (const auto& layer : mMapLayers)
	{
		layer->Render();
	}
}

void GameMap::Update()
{
	for (const auto& layer : mMapLayers)
	{
		layer->Update();
	}
}

void GameMap::Clean()
{
	for (const auto& layer : mMapLayers)
	{
		delete layer;
	}
	mMapLayers.clear();
}

std::vector<TileLayer*> GameMap::getMapLayers()
{
	return mMapLayers;
}

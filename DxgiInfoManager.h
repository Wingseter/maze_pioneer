#pragma once
#include "WinDef.h"
#include <vector>

class DxgiInfoManager
{
public:
	DxgiInfoManager();
	~DxgiInfoManager();
	DxgiInfoManager(const DxgiInfoManager&) = delete;
	DxgiInfoManager& operator=(const DxgiInfoManager&) = delete;
	void Set() noexcept;
	std::vector<std::string> GetMessage() const;
private:
	unsigned long long next = 0;
	struct IDXGIInfoQueue* pDxgiInfoQueue = nullptr;
};
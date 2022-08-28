/******************************************************************************************
*	Chili DirectX Framework Version 16.07.20											  *
*	Graphics.cpp																		  *
*	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
*																						  *
*	This file is part of The Chili DirectX Framework.									  *
*																						  *
*	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
*	it under the terms of the GNU General Public License as published by				  *
*	the Free Software Foundation, either version 3 of the License, or					  *
*	(at your option) any later version.													  *
*																						  *
*	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
*	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
*	GNU General Public License for more details.										  *
*																						  *
*	You should have received a copy of the GNU General Public License					  *
*	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
******************************************************************************************/
#include "MainWindow.h"
#include "Graphics.h"
#include "DXErr.h"
#include "ChiliException.h"
#include <assert.h>
#include <string>
#include <array>

// Ignore the intellisense error "cannot open source file" for .shh files.
// They will be created during the build sequence before the preprocessor runs.
namespace FramebufferShaders
{
#include "FramebufferPS.shh"
#include "FramebufferVS.shh"
}

#pragma comment( lib,"d3d11.lib" )

#define CHILI_GFX_EXCEPTION( hr,note ) Graphics::Exception( hr,note,_CRT_WIDE(__FILE__),__LINE__ )

using Microsoft::WRL::ComPtr;

Graphics::Graphics(HWNDKey& key)
{
	assert(key.hWnd != nullptr);

	//////////////////////////////////////////////////////
	// create device and swap chain/get render target view
	DXGI_SWAP_CHAIN_DESC sd = {};
	sd.BufferCount = 1;
	sd.BufferDesc.Width = Graphics::ScreenWidth;
	sd.BufferDesc.Height = Graphics::ScreenHeight;
	sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 1;
	sd.BufferDesc.RefreshRate.Denominator = 60;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = key.hWnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;

	HRESULT				hr;
	UINT				createFlags = 0u;
#ifdef CHILI_USE_D3D_DEBUG_LAYER
#ifdef _DEBUG
	createFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
#endif

	// create device and front/back buffers
	if (FAILED(hr = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		createFlags,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&sd,
		&pSwapChain,
		&pDevice,
		nullptr,
		&pImmediateContext)))
	{
		throw CHILI_GFX_EXCEPTION(hr, L"Creating device and swap chain");
	}

	// get handle to backbuffer
	ComPtr<ID3D11Resource> pBackBuffer;
	if (FAILED(hr = pSwapChain->GetBuffer(
		0,
		__uuidof(ID3D11Texture2D),
		(LPVOID*)&pBackBuffer)))
	{
		throw CHILI_GFX_EXCEPTION(hr, L"Getting back buffer");
	}

	// create a view on backbuffer that we can render to
	if (FAILED(hr = pDevice->CreateRenderTargetView(
		pBackBuffer.Get(),
		nullptr,
		&pRenderTargetView)))
	{
		throw CHILI_GFX_EXCEPTION(hr, L"Creating render target view on backbuffer");
	}


	// set backbuffer as the render target using created view
	pImmediateContext->OMSetRenderTargets(1, pRenderTargetView.GetAddressOf(), nullptr);


	// set viewport dimensions
	D3D11_VIEWPORT vp;
	vp.Width = float(Graphics::ScreenWidth);
	vp.Height = float(Graphics::ScreenHeight);
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0.0f;
	vp.TopLeftY = 0.0f;
	pImmediateContext->RSSetViewports(1, &vp);


	///////////////////////////////////////
	// create texture for cpu render target
	D3D11_TEXTURE2D_DESC sysTexDesc;
	sysTexDesc.Width = Graphics::ScreenWidth;
	sysTexDesc.Height = Graphics::ScreenHeight;
	sysTexDesc.MipLevels = 1;
	sysTexDesc.ArraySize = 1;
	sysTexDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	sysTexDesc.SampleDesc.Count = 1;
	sysTexDesc.SampleDesc.Quality = 0;
	sysTexDesc.Usage = D3D11_USAGE_DYNAMIC;
	sysTexDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	sysTexDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	sysTexDesc.MiscFlags = 0;
	// create the texture
	if (FAILED(hr = pDevice->CreateTexture2D(&sysTexDesc, nullptr, &pSysBufferTexture)))
	{
		throw CHILI_GFX_EXCEPTION(hr, L"Creating sysbuffer texture");
	}

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Format = sysTexDesc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;
	// create the resource view on the texture
	if (FAILED(hr = pDevice->CreateShaderResourceView(pSysBufferTexture.Get(),
		&srvDesc, &pSysBufferTextureView)))
	{
		throw CHILI_GFX_EXCEPTION(hr, L"Creating view on sysBuffer texture");
	}


	////////////////////////////////////////////////
	// create pixel shader for framebuffer
	// Ignore the intellisense error "namespace has no member"
	if (FAILED(hr = pDevice->CreatePixelShader(
		FramebufferShaders::FramebufferPSBytecode,
		sizeof(FramebufferShaders::FramebufferPSBytecode),
		nullptr,
		&pPixelShader)))
	{
		throw CHILI_GFX_EXCEPTION(hr, L"Creating pixel shader");
	}


	/////////////////////////////////////////////////
	// create vertex shader for framebuffer
	// Ignore the intellisense error "namespace has no member"
	if (FAILED(hr = pDevice->CreateVertexShader(
		FramebufferShaders::FramebufferVSBytecode,
		sizeof(FramebufferShaders::FramebufferVSBytecode),
		nullptr,
		&pVertexShader)))
	{
		throw CHILI_GFX_EXCEPTION(hr, L"Creating vertex shader");
	}


	//////////////////////////////////////////////////////////////
	// create and fill vertex buffer with quad for rendering frame
	const FSQVertex vertices[] =
	{
		{ -1.0f,1.0f,0.5f,0.0f,0.0f },
		{ 1.0f,1.0f,0.5f,1.0f,0.0f },
		{ 1.0f,-1.0f,0.5f,1.0f,1.0f },
		{ -1.0f,1.0f,0.5f,0.0f,0.0f },
		{ 1.0f,-1.0f,0.5f,1.0f,1.0f },
		{ -1.0f,-1.0f,0.5f,0.0f,1.0f },
	};
	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(FSQVertex) * 6;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0u;
	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = vertices;
	if (FAILED(hr = pDevice->CreateBuffer(&bd, &initData, &pVertexBuffer)))
	{
		throw CHILI_GFX_EXCEPTION(hr, L"Creating vertex buffer");
	}


	//////////////////////////////////////////
	// create input layout for fullscreen quad
	const D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{ "POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
		{ "TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0 }
	};

	// Ignore the intellisense error "namespace has no member"
	if (FAILED(hr = pDevice->CreateInputLayout(ied, 2,
		FramebufferShaders::FramebufferVSBytecode,
		sizeof(FramebufferShaders::FramebufferVSBytecode),
		&pInputLayout)))
	{
		throw CHILI_GFX_EXCEPTION(hr, L"Creating input layout");
	}


	////////////////////////////////////////////////////
	// Create sampler state for fullscreen textured quad
	D3D11_SAMPLER_DESC sampDesc = {};
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	if (FAILED(hr = pDevice->CreateSamplerState(&sampDesc, &pSamplerState)))
	{
		throw CHILI_GFX_EXCEPTION(hr, L"Creating sampler state");
	}

	// allocate memory for sysbuffer (16-byte aligned for faster access)
	pSysBuffer = reinterpret_cast<Color*>(
		_aligned_malloc(sizeof(Color) * Graphics::ScreenWidth * Graphics::ScreenHeight, 16u));
}

Graphics::~Graphics()
{
	// free sysbuffer memory (aligned free)
	if (pSysBuffer)
	{
		_aligned_free(pSysBuffer);
		pSysBuffer = nullptr;
	}
	// clear the state of the device context before destruction
	if (pImmediateContext) pImmediateContext->ClearState();
}

void Graphics::EndFrame()
{
	HRESULT hr;

	// lock and map the adapter memory for copying over the sysbuffer
	if (FAILED(hr = pImmediateContext->Map(pSysBufferTexture.Get(), 0u,
		D3D11_MAP_WRITE_DISCARD, 0u, &mappedSysBufferTexture)))
	{
		throw CHILI_GFX_EXCEPTION(hr, L"Mapping sysbuffer");
	}
	// setup parameters for copy operation
	Color* pDst = reinterpret_cast<Color*>(mappedSysBufferTexture.pData);
	const size_t dstPitch = mappedSysBufferTexture.RowPitch / sizeof(Color);
	const size_t srcPitch = Graphics::ScreenWidth;
	const size_t rowBytes = srcPitch * sizeof(Color);
	// perform the copy line-by-line
	for (size_t y = 0u; y < Graphics::ScreenHeight; y++)
	{
		memcpy(&pDst[y * dstPitch], &pSysBuffer[y * srcPitch], rowBytes);
	}
	// release the adapter memory
	pImmediateContext->Unmap(pSysBufferTexture.Get(), 0u);

	// render offscreen scene texture to back buffer
	pImmediateContext->IASetInputLayout(pInputLayout.Get());
	pImmediateContext->VSSetShader(pVertexShader.Get(), nullptr, 0u);
	pImmediateContext->PSSetShader(pPixelShader.Get(), nullptr, 0u);
	pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	const UINT stride = sizeof(FSQVertex);
	const UINT offset = 0u;
	pImmediateContext->IASetVertexBuffers(0u, 1u, pVertexBuffer.GetAddressOf(), &stride, &offset);
	pImmediateContext->PSSetShaderResources(0u, 1u, pSysBufferTextureView.GetAddressOf());
	pImmediateContext->PSSetSamplers(0u, 1u, pSamplerState.GetAddressOf());
	pImmediateContext->Draw(6u, 0u);

	// flip back/front buffers
	if (FAILED(hr = pSwapChain->Present(1u, 0u)))
	{
		if (hr == DXGI_ERROR_DEVICE_REMOVED)
		{
			throw CHILI_GFX_EXCEPTION(pDevice->GetDeviceRemovedReason(), L"Presenting back buffer [device removed]");
		}
		else
		{
			throw CHILI_GFX_EXCEPTION(hr, L"Presenting back buffer");
		}
	}
}

void Graphics::BeginFrame()
{
	// clear the sysbuffer
	memset(pSysBuffer, 0u, sizeof(Color) * Graphics::ScreenHeight * Graphics::ScreenWidth);
}

void Graphics::PutPixel(int x, int y, Color c)
{
	assert(x >= 0);
	assert(x < int(Graphics::ScreenWidth));
	assert(y >= 0);
	assert(y < int(Graphics::ScreenHeight));
	pSysBuffer[Graphics::ScreenWidth * y + x] = c;
}

void Graphics::DrawGameOver(int x, int y)
{
	PutPixel(3 + x, 0 + y, 255, 255, 255);
	PutPixel(4 + x, 0 + y, 254, 254, 254);
	PutPixel(5 + x, 0 + y, 254, 254, 254);
	PutPixel(6 + x, 0 + y, 255, 255, 255);
	PutPixel(7 + x, 0 + y, 255, 255, 255);
	PutPixel(8 + x, 0 + y, 255, 255, 255);
	PutPixel(9 + x, 0 + y, 254, 254, 254);
	PutPixel(10 + x, 0 + y, 255, 255, 255);
	PutPixel(15 + x, 0 + y, 254, 254, 254);
	PutPixel(16 + x, 0 + y, 255, 255, 255);
	PutPixel(17 + x, 0 + y, 255, 255, 255);
	PutPixel(18 + x, 0 + y, 255, 255, 255);
	PutPixel(19 + x, 0 + y, 255, 255, 255);
	PutPixel(25 + x, 0 + y, 255, 255, 255);
	PutPixel(26 + x, 0 + y, 255, 255, 255);
	PutPixel(27 + x, 0 + y, 255, 255, 255);
	PutPixel(28 + x, 0 + y, 254, 254, 254);
	PutPixel(33 + x, 0 + y, 254, 254, 254);
	PutPixel(34 + x, 0 + y, 255, 255, 255);
	PutPixel(35 + x, 0 + y, 255, 255, 255);
	PutPixel(36 + x, 0 + y, 255, 255, 255);
	PutPixel(37 + x, 0 + y, 255, 255, 255);
	PutPixel(40 + x, 0 + y, 254, 254, 254);
	PutPixel(41 + x, 0 + y, 255, 255, 255);
	PutPixel(42 + x, 0 + y, 255, 255, 255);
	PutPixel(43 + x, 0 + y, 255, 255, 255);
	PutPixel(44 + x, 0 + y, 255, 255, 255);
	PutPixel(45 + x, 0 + y, 255, 255, 255);
	PutPixel(46 + x, 0 + y, 255, 255, 255);
	PutPixel(47 + x, 0 + y, 254, 254, 254);
	PutPixel(2 + x, 1 + y, 254, 254, 254);
	PutPixel(3 + x, 1 + y, 255, 255, 255);
	PutPixel(4 + x, 1 + y, 255, 255, 255);
	PutPixel(5 + x, 1 + y, 255, 255, 255);
	PutPixel(6 + x, 1 + y, 255, 255, 255);
	PutPixel(7 + x, 1 + y, 255, 255, 255);
	PutPixel(8 + x, 1 + y, 255, 255, 255);
	PutPixel(9 + x, 1 + y, 255, 255, 255);
	PutPixel(10 + x, 1 + y, 255, 255, 255);
	PutPixel(15 + x, 1 + y, 254, 254, 254);
	PutPixel(16 + x, 1 + y, 255, 255, 255);
	PutPixel(17 + x, 1 + y, 255, 255, 255);
	PutPixel(18 + x, 1 + y, 255, 255, 255);
	PutPixel(19 + x, 1 + y, 255, 255, 255);
	PutPixel(25 + x, 1 + y, 255, 255, 255);
	PutPixel(26 + x, 1 + y, 255, 255, 255);
	PutPixel(27 + x, 1 + y, 255, 255, 255);
	PutPixel(28 + x, 1 + y, 255, 255, 255);
	PutPixel(29 + x, 1 + y, 255, 255, 255);
	PutPixel(33 + x, 1 + y, 254, 254, 254);
	PutPixel(34 + x, 1 + y, 255, 255, 255);
	PutPixel(35 + x, 1 + y, 255, 255, 255);
	PutPixel(36 + x, 1 + y, 255, 255, 255);
	PutPixel(37 + x, 1 + y, 255, 255, 255);
	PutPixel(40 + x, 1 + y, 254, 254, 254);
	PutPixel(41 + x, 1 + y, 255, 255, 255);
	PutPixel(42 + x, 1 + y, 255, 255, 255);
	PutPixel(43 + x, 1 + y, 255, 255, 255);
	PutPixel(44 + x, 1 + y, 255, 255, 255);
	PutPixel(45 + x, 1 + y, 255, 255, 255);
	PutPixel(46 + x, 1 + y, 255, 255, 255);
	PutPixel(47 + x, 1 + y, 254, 254, 254);
	PutPixel(1 + x, 2 + y, 254, 254, 254);
	PutPixel(2 + x, 2 + y, 255, 255, 255);
	PutPixel(3 + x, 2 + y, 255, 255, 255);
	PutPixel(4 + x, 2 + y, 255, 255, 255);
	PutPixel(5 + x, 2 + y, 254, 254, 254);
	PutPixel(6 + x, 2 + y, 254, 254, 254);
	PutPixel(7 + x, 2 + y, 254, 254, 254);
	PutPixel(8 + x, 2 + y, 254, 254, 254);
	PutPixel(9 + x, 2 + y, 254, 254, 254);
	PutPixel(14 + x, 2 + y, 255, 255, 255);
	PutPixel(15 + x, 2 + y, 255, 255, 255);
	PutPixel(16 + x, 2 + y, 255, 255, 255);
	PutPixel(17 + x, 2 + y, 255, 255, 255);
	PutPixel(18 + x, 2 + y, 255, 255, 255);
	PutPixel(19 + x, 2 + y, 255, 255, 255);
	PutPixel(25 + x, 2 + y, 255, 255, 255);
	PutPixel(26 + x, 2 + y, 255, 255, 255);
	PutPixel(27 + x, 2 + y, 255, 255, 255);
	PutPixel(28 + x, 2 + y, 255, 255, 255);
	PutPixel(29 + x, 2 + y, 254, 254, 254);
	PutPixel(32 + x, 2 + y, 255, 255, 255);
	PutPixel(33 + x, 2 + y, 255, 255, 255);
	PutPixel(34 + x, 2 + y, 255, 255, 255);
	PutPixel(35 + x, 2 + y, 255, 255, 255);
	PutPixel(36 + x, 2 + y, 255, 255, 255);
	PutPixel(37 + x, 2 + y, 254, 254, 254);
	PutPixel(40 + x, 2 + y, 254, 254, 254);
	PutPixel(41 + x, 2 + y, 255, 255, 255);
	PutPixel(42 + x, 2 + y, 255, 255, 255);
	PutPixel(43 + x, 2 + y, 254, 254, 254);
	PutPixel(44 + x, 2 + y, 254, 254, 254);
	PutPixel(45 + x, 2 + y, 254, 254, 254);
	PutPixel(46 + x, 2 + y, 254, 254, 254);
	PutPixel(47 + x, 2 + y, 255, 255, 255);
	PutPixel(0 + x, 3 + y, 255, 255, 255);
	PutPixel(1 + x, 3 + y, 255, 255, 255);
	PutPixel(2 + x, 3 + y, 255, 255, 255);
	PutPixel(3 + x, 3 + y, 255, 255, 255);
	PutPixel(4 + x, 3 + y, 254, 254, 254);
	PutPixel(9 + x, 3 + y, 255, 255, 255);
	PutPixel(14 + x, 3 + y, 255, 255, 255);
	PutPixel(15 + x, 3 + y, 255, 255, 255);
	PutPixel(16 + x, 3 + y, 255, 255, 255);
	PutPixel(17 + x, 3 + y, 254, 254, 254);
	PutPixel(18 + x, 3 + y, 255, 255, 255);
	PutPixel(19 + x, 3 + y, 255, 255, 255);
	PutPixel(20 + x, 3 + y, 255, 255, 255);
	PutPixel(24 + x, 3 + y, 255, 255, 255);
	PutPixel(25 + x, 3 + y, 255, 255, 255);
	PutPixel(26 + x, 3 + y, 255, 255, 255);
	PutPixel(27 + x, 3 + y, 255, 255, 255);
	PutPixel(28 + x, 3 + y, 255, 255, 255);
	PutPixel(29 + x, 3 + y, 255, 255, 255);
	PutPixel(32 + x, 3 + y, 255, 255, 255);
	PutPixel(33 + x, 3 + y, 255, 255, 255);
	PutPixel(34 + x, 3 + y, 254, 254, 254);
	PutPixel(35 + x, 3 + y, 255, 255, 255);
	PutPixel(36 + x, 3 + y, 255, 255, 255);
	PutPixel(37 + x, 3 + y, 254, 254, 254);
	PutPixel(40 + x, 3 + y, 254, 254, 254);
	PutPixel(41 + x, 3 + y, 255, 255, 255);
	PutPixel(42 + x, 3 + y, 255, 255, 255);
	PutPixel(0 + x, 4 + y, 254, 254, 254);
	PutPixel(1 + x, 4 + y, 255, 255, 255);
	PutPixel(2 + x, 4 + y, 255, 255, 255);
	PutPixel(3 + x, 4 + y, 254, 254, 254);
	PutPixel(14 + x, 4 + y, 254, 254, 254);
	PutPixel(15 + x, 4 + y, 255, 255, 255);
	PutPixel(16 + x, 4 + y, 255, 255, 255);
	PutPixel(17 + x, 4 + y, 255, 255, 255);
	PutPixel(18 + x, 4 + y, 255, 255, 255);
	PutPixel(19 + x, 4 + y, 255, 255, 255);
	PutPixel(20 + x, 4 + y, 255, 255, 255);
	PutPixel(24 + x, 4 + y, 255, 255, 255);
	PutPixel(25 + x, 4 + y, 255, 255, 255);
	PutPixel(26 + x, 4 + y, 255, 255, 255);
	PutPixel(27 + x, 4 + y, 254, 254, 254);
	PutPixel(28 + x, 4 + y, 255, 255, 255);
	PutPixel(29 + x, 4 + y, 254, 254, 254);
	PutPixel(32 + x, 4 + y, 255, 255, 255);
	PutPixel(33 + x, 4 + y, 255, 255, 255);
	PutPixel(34 + x, 4 + y, 255, 255, 255);
	PutPixel(35 + x, 4 + y, 255, 255, 255);
	PutPixel(36 + x, 4 + y, 255, 255, 255);
	PutPixel(37 + x, 4 + y, 254, 254, 254);
	PutPixel(40 + x, 4 + y, 254, 254, 254);
	PutPixel(41 + x, 4 + y, 255, 255, 255);
	PutPixel(42 + x, 4 + y, 255, 255, 255);
	PutPixel(0 + x, 5 + y, 254, 254, 254);
	PutPixel(1 + x, 5 + y, 255, 255, 255);
	PutPixel(2 + x, 5 + y, 255, 255, 255);
	PutPixel(3 + x, 5 + y, 255, 255, 255);
	PutPixel(14 + x, 5 + y, 254, 254, 254);
	PutPixel(15 + x, 5 + y, 255, 255, 255);
	PutPixel(16 + x, 5 + y, 254, 254, 254);
	PutPixel(17 + x, 5 + y, 255, 255, 255);
	PutPixel(18 + x, 5 + y, 255, 255, 255);
	PutPixel(19 + x, 5 + y, 255, 255, 255);
	PutPixel(20 + x, 5 + y, 255, 255, 255);
	PutPixel(24 + x, 5 + y, 255, 255, 255);
	PutPixel(25 + x, 5 + y, 255, 255, 255);
	PutPixel(26 + x, 5 + y, 255, 255, 255);
	PutPixel(27 + x, 5 + y, 254, 254, 254);
	PutPixel(28 + x, 5 + y, 255, 255, 255);
	PutPixel(29 + x, 5 + y, 255, 255, 255);
	PutPixel(30 + x, 5 + y, 255, 255, 255);
	PutPixel(32 + x, 5 + y, 255, 255, 255);
	PutPixel(33 + x, 5 + y, 255, 255, 255);
	PutPixel(34 + x, 5 + y, 255, 255, 255);
	PutPixel(35 + x, 5 + y, 255, 255, 255);
	PutPixel(36 + x, 5 + y, 255, 255, 255);
	PutPixel(37 + x, 5 + y, 254, 254, 254);
	PutPixel(40 + x, 5 + y, 254, 254, 254);
	PutPixel(41 + x, 5 + y, 255, 255, 255);
	PutPixel(42 + x, 5 + y, 255, 255, 255);
	PutPixel(0 + x, 6 + y, 254, 254, 254);
	PutPixel(1 + x, 6 + y, 255, 255, 255);
	PutPixel(2 + x, 6 + y, 255, 255, 255);
	PutPixel(6 + x, 6 + y, 254, 254, 254);
	PutPixel(7 + x, 6 + y, 254, 254, 254);
	PutPixel(8 + x, 6 + y, 254, 254, 254);
	PutPixel(9 + x, 6 + y, 254, 254, 254);
	PutPixel(10 + x, 6 + y, 255, 255, 255);
	PutPixel(13 + x, 6 + y, 255, 255, 255);
	PutPixel(14 + x, 6 + y, 255, 255, 255);
	PutPixel(15 + x, 6 + y, 255, 255, 255);
	PutPixel(16 + x, 6 + y, 255, 255, 255);
	PutPixel(18 + x, 6 + y, 255, 255, 255);
	PutPixel(19 + x, 6 + y, 255, 255, 255);
	PutPixel(20 + x, 6 + y, 255, 255, 255);
	PutPixel(24 + x, 6 + y, 255, 255, 255);
	PutPixel(25 + x, 6 + y, 255, 255, 255);
	PutPixel(26 + x, 6 + y, 255, 255, 255);
	PutPixel(27 + x, 6 + y, 255, 255, 255);
	PutPixel(28 + x, 6 + y, 255, 255, 255);
	PutPixel(29 + x, 6 + y, 255, 255, 255);
	PutPixel(30 + x, 6 + y, 255, 255, 255);
	PutPixel(31 + x, 6 + y, 255, 255, 255);
	PutPixel(32 + x, 6 + y, 255, 255, 255);
	PutPixel(33 + x, 6 + y, 255, 255, 255);
	PutPixel(34 + x, 6 + y, 255, 255, 255);
	PutPixel(35 + x, 6 + y, 255, 255, 255);
	PutPixel(36 + x, 6 + y, 255, 255, 255);
	PutPixel(37 + x, 6 + y, 254, 254, 254);
	PutPixel(40 + x, 6 + y, 254, 254, 254);
	PutPixel(41 + x, 6 + y, 255, 255, 255);
	PutPixel(42 + x, 6 + y, 255, 255, 255);
	PutPixel(43 + x, 6 + y, 255, 255, 255);
	PutPixel(44 + x, 6 + y, 255, 255, 255);
	PutPixel(45 + x, 6 + y, 255, 255, 255);
	PutPixel(46 + x, 6 + y, 255, 255, 255);
	PutPixel(47 + x, 6 + y, 254, 254, 254);
	PutPixel(0 + x, 7 + y, 255, 255, 255);
	PutPixel(1 + x, 7 + y, 255, 255, 255);
	PutPixel(2 + x, 7 + y, 254, 254, 254);
	PutPixel(6 + x, 7 + y, 255, 255, 255);
	PutPixel(7 + x, 7 + y, 255, 255, 255);
	PutPixel(8 + x, 7 + y, 255, 255, 255);
	PutPixel(9 + x, 7 + y, 255, 255, 255);
	PutPixel(10 + x, 7 + y, 254, 254, 254);
	PutPixel(13 + x, 7 + y, 255, 255, 255);
	PutPixel(14 + x, 7 + y, 255, 255, 255);
	PutPixel(15 + x, 7 + y, 255, 255, 255);
	PutPixel(16 + x, 7 + y, 255, 255, 255);
	PutPixel(18 + x, 7 + y, 254, 254, 254);
	PutPixel(19 + x, 7 + y, 255, 255, 255);
	PutPixel(20 + x, 7 + y, 255, 255, 255);
	PutPixel(21 + x, 7 + y, 255, 255, 255);
	PutPixel(24 + x, 7 + y, 255, 255, 255);
	PutPixel(25 + x, 7 + y, 255, 255, 255);
	PutPixel(26 + x, 7 + y, 255, 255, 255);
	PutPixel(27 + x, 7 + y, 255, 255, 255);
	PutPixel(28 + x, 7 + y, 255, 255, 255);
	PutPixel(29 + x, 7 + y, 255, 255, 255);
	PutPixel(30 + x, 7 + y, 255, 255, 255);
	PutPixel(31 + x, 7 + y, 255, 255, 255);
	PutPixel(32 + x, 7 + y, 255, 255, 255);
	PutPixel(33 + x, 7 + y, 254, 254, 254);
	PutPixel(35 + x, 7 + y, 255, 255, 255);
	PutPixel(36 + x, 7 + y, 255, 255, 255);
	PutPixel(37 + x, 7 + y, 254, 254, 254);
	PutPixel(40 + x, 7 + y, 254, 254, 254);
	PutPixel(41 + x, 7 + y, 255, 255, 255);
	PutPixel(42 + x, 7 + y, 255, 255, 255);
	PutPixel(43 + x, 7 + y, 255, 255, 255);
	PutPixel(44 + x, 7 + y, 255, 255, 255);
	PutPixel(45 + x, 7 + y, 255, 255, 255);
	PutPixel(46 + x, 7 + y, 255, 255, 255);
	PutPixel(47 + x, 7 + y, 254, 254, 254);
	PutPixel(0 + x, 8 + y, 255, 255, 255);
	PutPixel(1 + x, 8 + y, 255, 255, 255);
	PutPixel(2 + x, 8 + y, 254, 254, 254);
	PutPixel(6 + x, 8 + y, 255, 255, 255);
	PutPixel(7 + x, 8 + y, 255, 255, 255);
	PutPixel(8 + x, 8 + y, 255, 255, 255);
	PutPixel(9 + x, 8 + y, 255, 255, 255);
	PutPixel(10 + x, 8 + y, 254, 254, 254);
	PutPixel(13 + x, 8 + y, 254, 254, 254);
	PutPixel(14 + x, 8 + y, 255, 255, 255);
	PutPixel(15 + x, 8 + y, 255, 255, 255);
	PutPixel(16 + x, 8 + y, 254, 254, 254);
	PutPixel(17 + x, 8 + y, 254, 254, 254);
	PutPixel(18 + x, 8 + y, 254, 254, 254);
	PutPixel(19 + x, 8 + y, 255, 255, 255);
	PutPixel(20 + x, 8 + y, 255, 255, 255);
	PutPixel(21 + x, 8 + y, 255, 255, 255);
	PutPixel(24 + x, 8 + y, 255, 255, 255);
	PutPixel(25 + x, 8 + y, 255, 255, 255);
	PutPixel(26 + x, 8 + y, 255, 255, 255);
	PutPixel(27 + x, 8 + y, 255, 255, 255);
	PutPixel(28 + x, 8 + y, 254, 254, 254);
	PutPixel(29 + x, 8 + y, 255, 255, 255);
	PutPixel(30 + x, 8 + y, 254, 254, 254);
	PutPixel(31 + x, 8 + y, 254, 254, 254);
	PutPixel(32 + x, 8 + y, 255, 255, 255);
	PutPixel(33 + x, 8 + y, 255, 255, 255);
	PutPixel(35 + x, 8 + y, 255, 255, 255);
	PutPixel(36 + x, 8 + y, 255, 255, 255);
	PutPixel(37 + x, 8 + y, 254, 254, 254);
	PutPixel(40 + x, 8 + y, 254, 254, 254);
	PutPixel(41 + x, 8 + y, 255, 255, 255);
	PutPixel(42 + x, 8 + y, 255, 255, 255);
	PutPixel(43 + x, 8 + y, 254, 254, 254);
	PutPixel(44 + x, 8 + y, 254, 254, 254);
	PutPixel(45 + x, 8 + y, 254, 254, 254);
	PutPixel(46 + x, 8 + y, 254, 254, 254);
	PutPixel(47 + x, 8 + y, 255, 255, 255);
	PutPixel(0 + x, 9 + y, 255, 255, 255);
	PutPixel(1 + x, 9 + y, 255, 255, 255);
	PutPixel(2 + x, 9 + y, 255, 255, 255);
	PutPixel(3 + x, 9 + y, 255, 255, 255);
	PutPixel(8 + x, 9 + y, 255, 255, 255);
	PutPixel(9 + x, 9 + y, 255, 255, 255);
	PutPixel(10 + x, 9 + y, 254, 254, 254);
	PutPixel(13 + x, 9 + y, 254, 254, 254);
	PutPixel(14 + x, 9 + y, 255, 255, 255);
	PutPixel(15 + x, 9 + y, 255, 255, 255);
	PutPixel(16 + x, 9 + y, 255, 255, 255);
	PutPixel(17 + x, 9 + y, 255, 255, 255);
	PutPixel(18 + x, 9 + y, 255, 255, 255);
	PutPixel(19 + x, 9 + y, 255, 255, 255);
	PutPixel(20 + x, 9 + y, 255, 255, 255);
	PutPixel(21 + x, 9 + y, 255, 255, 255);
	PutPixel(24 + x, 9 + y, 254, 254, 254);
	PutPixel(25 + x, 9 + y, 255, 255, 255);
	PutPixel(26 + x, 9 + y, 255, 255, 255);
	PutPixel(28 + x, 9 + y, 255, 255, 255);
	PutPixel(29 + x, 9 + y, 255, 255, 255);
	PutPixel(30 + x, 9 + y, 254, 254, 254);
	PutPixel(31 + x, 9 + y, 254, 254, 254);
	PutPixel(32 + x, 9 + y, 255, 255, 255);
	PutPixel(33 + x, 9 + y, 255, 255, 255);
	PutPixel(35 + x, 9 + y, 255, 255, 255);
	PutPixel(36 + x, 9 + y, 255, 255, 255);
	PutPixel(37 + x, 9 + y, 254, 254, 254);
	PutPixel(40 + x, 9 + y, 254, 254, 254);
	PutPixel(41 + x, 9 + y, 255, 255, 255);
	PutPixel(42 + x, 9 + y, 255, 255, 255);
	PutPixel(0 + x, 10 + y, 254, 254, 254);
	PutPixel(1 + x, 10 + y, 255, 255, 255);
	PutPixel(2 + x, 10 + y, 255, 255, 255);
	PutPixel(3 + x, 10 + y, 254, 254, 254);
	PutPixel(8 + x, 10 + y, 255, 255, 255);
	PutPixel(9 + x, 10 + y, 255, 255, 255);
	PutPixel(10 + x, 10 + y, 254, 254, 254);
	PutPixel(12 + x, 10 + y, 255, 255, 255);
	PutPixel(13 + x, 10 + y, 255, 255, 255);
	PutPixel(14 + x, 10 + y, 255, 255, 255);
	PutPixel(15 + x, 10 + y, 255, 255, 255);
	PutPixel(16 + x, 10 + y, 255, 255, 255);
	PutPixel(17 + x, 10 + y, 255, 255, 255);
	PutPixel(18 + x, 10 + y, 255, 255, 255);
	PutPixel(19 + x, 10 + y, 255, 255, 255);
	PutPixel(20 + x, 10 + y, 255, 255, 255);
	PutPixel(21 + x, 10 + y, 255, 255, 255);
	PutPixel(24 + x, 10 + y, 254, 254, 254);
	PutPixel(25 + x, 10 + y, 255, 255, 255);
	PutPixel(26 + x, 10 + y, 255, 255, 255);
	PutPixel(28 + x, 10 + y, 255, 255, 255);
	PutPixel(29 + x, 10 + y, 255, 255, 255);
	PutPixel(30 + x, 10 + y, 255, 255, 255);
	PutPixel(31 + x, 10 + y, 254, 254, 254);
	PutPixel(32 + x, 10 + y, 255, 255, 255);
	PutPixel(33 + x, 10 + y, 255, 255, 255);
	PutPixel(35 + x, 10 + y, 255, 255, 255);
	PutPixel(36 + x, 10 + y, 255, 255, 255);
	PutPixel(37 + x, 10 + y, 254, 254, 254);
	PutPixel(40 + x, 10 + y, 254, 254, 254);
	PutPixel(41 + x, 10 + y, 255, 255, 255);
	PutPixel(42 + x, 10 + y, 255, 255, 255);
	PutPixel(0 + x, 11 + y, 255, 255, 255);
	PutPixel(1 + x, 11 + y, 255, 255, 255);
	PutPixel(2 + x, 11 + y, 255, 255, 255);
	PutPixel(3 + x, 11 + y, 255, 255, 255);
	PutPixel(4 + x, 11 + y, 254, 254, 254);
	PutPixel(8 + x, 11 + y, 255, 255, 255);
	PutPixel(9 + x, 11 + y, 255, 255, 255);
	PutPixel(10 + x, 11 + y, 254, 254, 254);
	PutPixel(12 + x, 11 + y, 255, 255, 255);
	PutPixel(13 + x, 11 + y, 255, 255, 255);
	PutPixel(14 + x, 11 + y, 255, 255, 255);
	PutPixel(15 + x, 11 + y, 254, 254, 254);
	PutPixel(19 + x, 11 + y, 255, 255, 255);
	PutPixel(20 + x, 11 + y, 255, 255, 255);
	PutPixel(21 + x, 11 + y, 255, 255, 255);
	PutPixel(22 + x, 11 + y, 255, 255, 255);
	PutPixel(24 + x, 11 + y, 254, 254, 254);
	PutPixel(25 + x, 11 + y, 255, 255, 255);
	PutPixel(26 + x, 11 + y, 255, 255, 255);
	PutPixel(29 + x, 11 + y, 254, 254, 254);
	PutPixel(30 + x, 11 + y, 255, 255, 255);
	PutPixel(31 + x, 11 + y, 255, 255, 255);
	PutPixel(32 + x, 11 + y, 255, 255, 255);
	PutPixel(35 + x, 11 + y, 254, 254, 254);
	PutPixel(36 + x, 11 + y, 255, 255, 255);
	PutPixel(37 + x, 11 + y, 254, 254, 254);
	PutPixel(40 + x, 11 + y, 254, 254, 254);
	PutPixel(41 + x, 11 + y, 255, 255, 255);
	PutPixel(42 + x, 11 + y, 255, 255, 255);
	PutPixel(1 + x, 12 + y, 255, 255, 255);
	PutPixel(2 + x, 12 + y, 255, 255, 255);
	PutPixel(3 + x, 12 + y, 255, 255, 255);
	PutPixel(4 + x, 12 + y, 255, 255, 255);
	PutPixel(5 + x, 12 + y, 254, 254, 254);
	PutPixel(6 + x, 12 + y, 254, 254, 254);
	PutPixel(7 + x, 12 + y, 254, 254, 254);
	PutPixel(8 + x, 12 + y, 255, 255, 255);
	PutPixel(9 + x, 12 + y, 255, 255, 255);
	PutPixel(10 + x, 12 + y, 254, 254, 254);
	PutPixel(12 + x, 12 + y, 254, 254, 254);
	PutPixel(13 + x, 12 + y, 255, 255, 255);
	PutPixel(14 + x, 12 + y, 255, 255, 255);
	PutPixel(15 + x, 12 + y, 255, 255, 255);
	PutPixel(19 + x, 12 + y, 255, 255, 255);
	PutPixel(20 + x, 12 + y, 255, 255, 255);
	PutPixel(21 + x, 12 + y, 255, 255, 255);
	PutPixel(22 + x, 12 + y, 255, 255, 255);
	PutPixel(24 + x, 12 + y, 254, 254, 254);
	PutPixel(25 + x, 12 + y, 255, 255, 255);
	PutPixel(26 + x, 12 + y, 255, 255, 255);
	PutPixel(29 + x, 12 + y, 255, 255, 255);
	PutPixel(30 + x, 12 + y, 255, 255, 255);
	PutPixel(31 + x, 12 + y, 255, 255, 255);
	PutPixel(32 + x, 12 + y, 255, 255, 255);
	PutPixel(35 + x, 12 + y, 254, 254, 254);
	PutPixel(36 + x, 12 + y, 255, 255, 255);
	PutPixel(37 + x, 12 + y, 254, 254, 254);
	PutPixel(40 + x, 12 + y, 254, 254, 254);
	PutPixel(41 + x, 12 + y, 255, 255, 255);
	PutPixel(42 + x, 12 + y, 255, 255, 255);
	PutPixel(43 + x, 12 + y, 254, 254, 254);
	PutPixel(44 + x, 12 + y, 254, 254, 254);
	PutPixel(45 + x, 12 + y, 254, 254, 254);
	PutPixel(46 + x, 12 + y, 254, 254, 254);
	PutPixel(47 + x, 12 + y, 254, 254, 254);
	PutPixel(1 + x, 13 + y, 255, 255, 255);
	PutPixel(2 + x, 13 + y, 255, 255, 255);
	PutPixel(3 + x, 13 + y, 255, 255, 255);
	PutPixel(4 + x, 13 + y, 255, 255, 255);
	PutPixel(5 + x, 13 + y, 255, 255, 255);
	PutPixel(6 + x, 13 + y, 255, 255, 255);
	PutPixel(7 + x, 13 + y, 255, 255, 255);
	PutPixel(8 + x, 13 + y, 255, 255, 255);
	PutPixel(9 + x, 13 + y, 255, 255, 255);
	PutPixel(10 + x, 13 + y, 254, 254, 254);
	PutPixel(12 + x, 13 + y, 254, 254, 254);
	PutPixel(13 + x, 13 + y, 255, 255, 255);
	PutPixel(14 + x, 13 + y, 255, 255, 255);
	PutPixel(19 + x, 13 + y, 255, 255, 255);
	PutPixel(20 + x, 13 + y, 255, 255, 255);
	PutPixel(21 + x, 13 + y, 255, 255, 255);
	PutPixel(22 + x, 13 + y, 254, 254, 254);
	PutPixel(24 + x, 13 + y, 255, 255, 255);
	PutPixel(25 + x, 13 + y, 255, 255, 255);
	PutPixel(26 + x, 13 + y, 255, 255, 255);
	PutPixel(29 + x, 13 + y, 254, 254, 254);
	PutPixel(30 + x, 13 + y, 255, 255, 255);
	PutPixel(31 + x, 13 + y, 255, 255, 255);
	PutPixel(32 + x, 13 + y, 255, 255, 255);
	PutPixel(35 + x, 13 + y, 254, 254, 254);
	PutPixel(36 + x, 13 + y, 255, 255, 255);
	PutPixel(37 + x, 13 + y, 255, 255, 255);
	PutPixel(40 + x, 13 + y, 254, 254, 254);
	PutPixel(41 + x, 13 + y, 255, 255, 255);
	PutPixel(42 + x, 13 + y, 255, 255, 255);
	PutPixel(43 + x, 13 + y, 255, 255, 255);
	PutPixel(44 + x, 13 + y, 255, 255, 255);
	PutPixel(45 + x, 13 + y, 255, 255, 255);
	PutPixel(46 + x, 13 + y, 255, 255, 255);
	PutPixel(47 + x, 13 + y, 255, 255, 255);
	PutPixel(3 + x, 14 + y, 255, 255, 255);
	PutPixel(4 + x, 14 + y, 255, 255, 255);
	PutPixel(5 + x, 14 + y, 254, 254, 254);
	PutPixel(6 + x, 14 + y, 255, 255, 255);
	PutPixel(7 + x, 14 + y, 255, 255, 255);
	PutPixel(8 + x, 14 + y, 254, 254, 254);
	PutPixel(9 + x, 14 + y, 255, 255, 255);
	PutPixel(10 + x, 14 + y, 255, 255, 255);
	PutPixel(11 + x, 14 + y, 255, 255, 255);
	PutPixel(12 + x, 14 + y, 255, 255, 255);
	PutPixel(13 + x, 14 + y, 255, 255, 255);
	PutPixel(14 + x, 14 + y, 254, 254, 254);
	PutPixel(19 + x, 14 + y, 255, 255, 255);
	PutPixel(20 + x, 14 + y, 255, 255, 255);
	PutPixel(21 + x, 14 + y, 255, 255, 255);
	PutPixel(22 + x, 14 + y, 254, 254, 254);
	PutPixel(24 + x, 14 + y, 254, 254, 254);
	PutPixel(25 + x, 14 + y, 255, 255, 255);
	PutPixel(26 + x, 14 + y, 255, 255, 255);
	PutPixel(29 + x, 14 + y, 255, 255, 255);
	PutPixel(30 + x, 14 + y, 254, 254, 254);
	PutPixel(31 + x, 14 + y, 254, 254, 254);
	PutPixel(32 + x, 14 + y, 255, 255, 255);
	PutPixel(35 + x, 14 + y, 254, 254, 254);
	PutPixel(36 + x, 14 + y, 255, 255, 255);
	PutPixel(37 + x, 14 + y, 255, 255, 255);
	PutPixel(40 + x, 14 + y, 254, 254, 254);
	PutPixel(41 + x, 14 + y, 255, 255, 255);
	PutPixel(42 + x, 14 + y, 255, 255, 255);
	PutPixel(43 + x, 14 + y, 255, 255, 255);
	PutPixel(44 + x, 14 + y, 255, 255, 255);
	PutPixel(45 + x, 14 + y, 255, 255, 255);
	PutPixel(46 + x, 14 + y, 255, 255, 255);
	PutPixel(47 + x, 14 + y, 255, 255, 255);
	PutPixel(5 + x, 27 + y, 254, 254, 254);
	PutPixel(6 + x, 27 + y, 255, 255, 255);
	PutPixel(7 + x, 27 + y, 255, 255, 255);
	PutPixel(8 + x, 27 + y, 255, 255, 255);
	PutPixel(9 + x, 27 + y, 255, 255, 255);
	PutPixel(10 + x, 27 + y, 255, 255, 255);
	PutPixel(14 + x, 27 + y, 255, 255, 255);
	PutPixel(15 + x, 27 + y, 255, 255, 255);
	PutPixel(16 + x, 27 + y, 255, 255, 255);
	PutPixel(17 + x, 27 + y, 254, 254, 254);
	PutPixel(22 + x, 27 + y, 255, 255, 255);
	PutPixel(23 + x, 27 + y, 255, 255, 255);
	PutPixel(24 + x, 27 + y, 255, 255, 255);
	PutPixel(25 + x, 27 + y, 255, 255, 255);
	PutPixel(27 + x, 27 + y, 254, 254, 254);
	PutPixel(28 + x, 27 + y, 255, 255, 255);
	PutPixel(29 + x, 27 + y, 255, 255, 255);
	PutPixel(30 + x, 27 + y, 255, 255, 255);
	PutPixel(31 + x, 27 + y, 255, 255, 255);
	PutPixel(32 + x, 27 + y, 255, 255, 255);
	PutPixel(33 + x, 27 + y, 255, 255, 255);
	PutPixel(34 + x, 27 + y, 254, 254, 254);
	PutPixel(37 + x, 27 + y, 254, 254, 254);
	PutPixel(38 + x, 27 + y, 254, 254, 254);
	PutPixel(39 + x, 27 + y, 255, 255, 255);
	PutPixel(40 + x, 27 + y, 255, 255, 255);
	PutPixel(41 + x, 27 + y, 255, 255, 255);
	PutPixel(42 + x, 27 + y, 255, 255, 255);
	PutPixel(43 + x, 27 + y, 255, 255, 255);
	PutPixel(44 + x, 27 + y, 255, 255, 255);
	PutPixel(3 + x, 28 + y, 255, 255, 255);
	PutPixel(4 + x, 28 + y, 254, 254, 254);
	PutPixel(5 + x, 28 + y, 255, 255, 255);
	PutPixel(6 + x, 28 + y, 255, 255, 255);
	PutPixel(7 + x, 28 + y, 255, 255, 255);
	PutPixel(8 + x, 28 + y, 255, 255, 255);
	PutPixel(9 + x, 28 + y, 255, 255, 255);
	PutPixel(10 + x, 28 + y, 255, 255, 255);
	PutPixel(11 + x, 28 + y, 254, 254, 254);
	PutPixel(14 + x, 28 + y, 255, 255, 255);
	PutPixel(15 + x, 28 + y, 255, 255, 255);
	PutPixel(16 + x, 28 + y, 255, 255, 255);
	PutPixel(17 + x, 28 + y, 254, 254, 254);
	PutPixel(22 + x, 28 + y, 255, 255, 255);
	PutPixel(23 + x, 28 + y, 255, 255, 255);
	PutPixel(24 + x, 28 + y, 255, 255, 255);
	PutPixel(25 + x, 28 + y, 255, 255, 255);
	PutPixel(27 + x, 28 + y, 254, 254, 254);
	PutPixel(28 + x, 28 + y, 255, 255, 255);
	PutPixel(29 + x, 28 + y, 255, 255, 255);
	PutPixel(30 + x, 28 + y, 255, 255, 255);
	PutPixel(31 + x, 28 + y, 255, 255, 255);
	PutPixel(32 + x, 28 + y, 255, 255, 255);
	PutPixel(33 + x, 28 + y, 255, 255, 255);
	PutPixel(34 + x, 28 + y, 254, 254, 254);
	PutPixel(37 + x, 28 + y, 255, 255, 255);
	PutPixel(38 + x, 28 + y, 255, 255, 255);
	PutPixel(39 + x, 28 + y, 255, 255, 255);
	PutPixel(40 + x, 28 + y, 255, 255, 255);
	PutPixel(41 + x, 28 + y, 255, 255, 255);
	PutPixel(42 + x, 28 + y, 255, 255, 255);
	PutPixel(43 + x, 28 + y, 255, 255, 255);
	PutPixel(44 + x, 28 + y, 255, 255, 255);
	PutPixel(45 + x, 28 + y, 255, 255, 255);
	PutPixel(3 + x, 29 + y, 255, 255, 255);
	PutPixel(4 + x, 29 + y, 255, 255, 255);
	PutPixel(5 + x, 29 + y, 255, 255, 255);
	PutPixel(6 + x, 29 + y, 255, 255, 255);
	PutPixel(7 + x, 29 + y, 254, 254, 254);
	PutPixel(8 + x, 29 + y, 255, 255, 255);
	PutPixel(9 + x, 29 + y, 255, 255, 255);
	PutPixel(10 + x, 29 + y, 255, 255, 255);
	PutPixel(11 + x, 29 + y, 255, 255, 255);
	PutPixel(12 + x, 29 + y, 254, 254, 254);
	PutPixel(15 + x, 29 + y, 255, 255, 255);
	PutPixel(16 + x, 29 + y, 255, 255, 255);
	PutPixel(17 + x, 29 + y, 255, 255, 255);
	PutPixel(18 + x, 29 + y, 255, 255, 255);
	PutPixel(22 + x, 29 + y, 254, 254, 254);
	PutPixel(23 + x, 29 + y, 255, 255, 255);
	PutPixel(24 + x, 29 + y, 255, 255, 255);
	PutPixel(25 + x, 29 + y, 255, 255, 255);
	PutPixel(27 + x, 29 + y, 254, 254, 254);
	PutPixel(28 + x, 29 + y, 255, 255, 255);
	PutPixel(29 + x, 29 + y, 255, 255, 255);
	PutPixel(30 + x, 29 + y, 254, 254, 254);
	PutPixel(31 + x, 29 + y, 254, 254, 254);
	PutPixel(32 + x, 29 + y, 254, 254, 254);
	PutPixel(33 + x, 29 + y, 254, 254, 254);
	PutPixel(34 + x, 29 + y, 255, 255, 255);
	PutPixel(37 + x, 29 + y, 255, 255, 255);
	PutPixel(38 + x, 29 + y, 255, 255, 255);
	PutPixel(39 + x, 29 + y, 254, 254, 254);
	PutPixel(40 + x, 29 + y, 254, 254, 254);
	PutPixel(41 + x, 29 + y, 255, 255, 255);
	PutPixel(42 + x, 29 + y, 254, 254, 254);
	PutPixel(43 + x, 29 + y, 255, 255, 255);
	PutPixel(44 + x, 29 + y, 255, 255, 255);
	PutPixel(45 + x, 29 + y, 254, 254, 254);
	PutPixel(2 + x, 30 + y, 255, 255, 255);
	PutPixel(3 + x, 30 + y, 255, 255, 255);
	PutPixel(4 + x, 30 + y, 255, 255, 255);
	PutPixel(5 + x, 30 + y, 254, 254, 254);
	PutPixel(6 + x, 30 + y, 255, 255, 255);
	PutPixel(9 + x, 30 + y, 255, 255, 255);
	PutPixel(10 + x, 30 + y, 255, 255, 255);
	PutPixel(11 + x, 30 + y, 255, 255, 255);
	PutPixel(12 + x, 30 + y, 254, 254, 254);
	PutPixel(13 + x, 30 + y, 255, 255, 255);
	PutPixel(15 + x, 30 + y, 255, 255, 255);
	PutPixel(16 + x, 30 + y, 255, 255, 255);
	PutPixel(17 + x, 30 + y, 255, 255, 255);
	PutPixel(18 + x, 30 + y, 254, 254, 254);
	PutPixel(22 + x, 30 + y, 254, 254, 254);
	PutPixel(23 + x, 30 + y, 255, 255, 255);
	PutPixel(24 + x, 30 + y, 255, 255, 255);
	PutPixel(27 + x, 30 + y, 254, 254, 254);
	PutPixel(28 + x, 30 + y, 255, 255, 255);
	PutPixel(29 + x, 30 + y, 255, 255, 255);
	PutPixel(37 + x, 30 + y, 255, 255, 255);
	PutPixel(38 + x, 30 + y, 255, 255, 255);
	PutPixel(39 + x, 30 + y, 254, 254, 254);
	PutPixel(42 + x, 30 + y, 255, 255, 255);
	PutPixel(43 + x, 30 + y, 255, 255, 255);
	PutPixel(44 + x, 30 + y, 255, 255, 255);
	PutPixel(45 + x, 30 + y, 255, 255, 255);
	PutPixel(2 + x, 31 + y, 255, 255, 255);
	PutPixel(3 + x, 31 + y, 255, 255, 255);
	PutPixel(4 + x, 31 + y, 255, 255, 255);
	PutPixel(5 + x, 31 + y, 255, 255, 255);
	PutPixel(10 + x, 31 + y, 254, 254, 254);
	PutPixel(11 + x, 31 + y, 255, 255, 255);
	PutPixel(12 + x, 31 + y, 255, 255, 255);
	PutPixel(13 + x, 31 + y, 255, 255, 255);
	PutPixel(15 + x, 31 + y, 255, 255, 255);
	PutPixel(16 + x, 31 + y, 255, 255, 255);
	PutPixel(17 + x, 31 + y, 255, 255, 255);
	PutPixel(18 + x, 31 + y, 255, 255, 255);
	PutPixel(21 + x, 31 + y, 255, 255, 255);
	PutPixel(22 + x, 31 + y, 255, 255, 255);
	PutPixel(23 + x, 31 + y, 255, 255, 255);
	PutPixel(24 + x, 31 + y, 255, 255, 255);
	PutPixel(27 + x, 31 + y, 254, 254, 254);
	PutPixel(28 + x, 31 + y, 255, 255, 255);
	PutPixel(29 + x, 31 + y, 255, 255, 255);
	PutPixel(37 + x, 31 + y, 255, 255, 255);
	PutPixel(38 + x, 31 + y, 255, 255, 255);
	PutPixel(39 + x, 31 + y, 254, 254, 254);
	PutPixel(43 + x, 31 + y, 255, 255, 255);
	PutPixel(44 + x, 31 + y, 255, 255, 255);
	PutPixel(45 + x, 31 + y, 254, 254, 254);
	PutPixel(2 + x, 32 + y, 254, 254, 254);
	PutPixel(3 + x, 32 + y, 255, 255, 255);
	PutPixel(4 + x, 32 + y, 255, 255, 255);
	PutPixel(10 + x, 32 + y, 255, 255, 255);
	PutPixel(11 + x, 32 + y, 255, 255, 255);
	PutPixel(12 + x, 32 + y, 255, 255, 255);
	PutPixel(13 + x, 32 + y, 255, 255, 255);
	PutPixel(16 + x, 32 + y, 255, 255, 255);
	PutPixel(17 + x, 32 + y, 255, 255, 255);
	PutPixel(18 + x, 32 + y, 254, 254, 254);
	PutPixel(21 + x, 32 + y, 255, 255, 255);
	PutPixel(22 + x, 32 + y, 255, 255, 255);
	PutPixel(23 + x, 32 + y, 255, 255, 255);
	PutPixel(24 + x, 32 + y, 254, 254, 254);
	PutPixel(27 + x, 32 + y, 254, 254, 254);
	PutPixel(28 + x, 32 + y, 255, 255, 255);
	PutPixel(29 + x, 32 + y, 255, 255, 255);
	PutPixel(37 + x, 32 + y, 255, 255, 255);
	PutPixel(38 + x, 32 + y, 255, 255, 255);
	PutPixel(39 + x, 32 + y, 254, 254, 254);
	PutPixel(42 + x, 32 + y, 255, 255, 255);
	PutPixel(43 + x, 32 + y, 255, 255, 255);
	PutPixel(44 + x, 32 + y, 255, 255, 255);
	PutPixel(45 + x, 32 + y, 254, 254, 254);
	PutPixel(2 + x, 33 + y, 255, 255, 255);
	PutPixel(3 + x, 33 + y, 255, 255, 255);
	PutPixel(4 + x, 33 + y, 254, 254, 254);
	PutPixel(11 + x, 33 + y, 255, 255, 255);
	PutPixel(12 + x, 33 + y, 255, 255, 255);
	PutPixel(13 + x, 33 + y, 254, 254, 254);
	PutPixel(16 + x, 33 + y, 254, 254, 254);
	PutPixel(17 + x, 33 + y, 255, 255, 255);
	PutPixel(18 + x, 33 + y, 255, 255, 255);
	PutPixel(19 + x, 33 + y, 255, 255, 255);
	PutPixel(21 + x, 33 + y, 254, 254, 254);
	PutPixel(22 + x, 33 + y, 255, 255, 255);
	PutPixel(23 + x, 33 + y, 255, 255, 255);
	PutPixel(24 + x, 33 + y, 255, 255, 255);
	PutPixel(27 + x, 33 + y, 254, 254, 254);
	PutPixel(28 + x, 33 + y, 255, 255, 255);
	PutPixel(29 + x, 33 + y, 255, 255, 255);
	PutPixel(30 + x, 33 + y, 255, 255, 255);
	PutPixel(31 + x, 33 + y, 255, 255, 255);
	PutPixel(32 + x, 33 + y, 255, 255, 255);
	PutPixel(33 + x, 33 + y, 255, 255, 255);
	PutPixel(34 + x, 33 + y, 254, 254, 254);
	PutPixel(37 + x, 33 + y, 255, 255, 255);
	PutPixel(38 + x, 33 + y, 255, 255, 255);
	PutPixel(39 + x, 33 + y, 254, 254, 254);
	PutPixel(41 + x, 33 + y, 255, 255, 255);
	PutPixel(42 + x, 33 + y, 254, 254, 254);
	PutPixel(43 + x, 33 + y, 255, 255, 255);
	PutPixel(44 + x, 33 + y, 255, 255, 255);
	PutPixel(45 + x, 33 + y, 255, 255, 255);
	PutPixel(2 + x, 34 + y, 255, 255, 255);
	PutPixel(3 + x, 34 + y, 255, 255, 255);
	PutPixel(4 + x, 34 + y, 254, 254, 254);
	PutPixel(11 + x, 34 + y, 255, 255, 255);
	PutPixel(12 + x, 34 + y, 255, 255, 255);
	PutPixel(13 + x, 34 + y, 254, 254, 254);
	PutPixel(16 + x, 34 + y, 254, 254, 254);
	PutPixel(17 + x, 34 + y, 255, 255, 255);
	PutPixel(18 + x, 34 + y, 255, 255, 255);
	PutPixel(19 + x, 34 + y, 255, 255, 255);
	PutPixel(21 + x, 34 + y, 254, 254, 254);
	PutPixel(22 + x, 34 + y, 255, 255, 255);
	PutPixel(23 + x, 34 + y, 254, 254, 254);
	PutPixel(27 + x, 34 + y, 254, 254, 254);
	PutPixel(28 + x, 34 + y, 255, 255, 255);
	PutPixel(29 + x, 34 + y, 255, 255, 255);
	PutPixel(30 + x, 34 + y, 255, 255, 255);
	PutPixel(31 + x, 34 + y, 255, 255, 255);
	PutPixel(32 + x, 34 + y, 255, 255, 255);
	PutPixel(33 + x, 34 + y, 255, 255, 255);
	PutPixel(34 + x, 34 + y, 254, 254, 254);
	PutPixel(37 + x, 34 + y, 255, 255, 255);
	PutPixel(38 + x, 34 + y, 255, 255, 255);
	PutPixel(39 + x, 34 + y, 255, 255, 255);
	PutPixel(40 + x, 34 + y, 255, 255, 255);
	PutPixel(41 + x, 34 + y, 255, 255, 255);
	PutPixel(42 + x, 34 + y, 255, 255, 255);
	PutPixel(43 + x, 34 + y, 255, 255, 255);
	PutPixel(44 + x, 34 + y, 254, 254, 254);
	PutPixel(2 + x, 35 + y, 255, 255, 255);
	PutPixel(3 + x, 35 + y, 255, 255, 255);
	PutPixel(4 + x, 35 + y, 254, 254, 254);
	PutPixel(11 + x, 35 + y, 255, 255, 255);
	PutPixel(12 + x, 35 + y, 255, 255, 255);
	PutPixel(13 + x, 35 + y, 254, 254, 254);
	PutPixel(16 + x, 35 + y, 255, 255, 255);
	PutPixel(17 + x, 35 + y, 255, 255, 255);
	PutPixel(18 + x, 35 + y, 255, 255, 255);
	PutPixel(19 + x, 35 + y, 255, 255, 255);
	PutPixel(20 + x, 35 + y, 255, 255, 255);
	PutPixel(21 + x, 35 + y, 255, 255, 255);
	PutPixel(22 + x, 35 + y, 255, 255, 255);
	PutPixel(23 + x, 35 + y, 254, 254, 254);
	PutPixel(27 + x, 35 + y, 254, 254, 254);
	PutPixel(28 + x, 35 + y, 255, 255, 255);
	PutPixel(29 + x, 35 + y, 255, 255, 255);
	PutPixel(30 + x, 35 + y, 254, 254, 254);
	PutPixel(31 + x, 35 + y, 254, 254, 254);
	PutPixel(32 + x, 35 + y, 254, 254, 254);
	PutPixel(33 + x, 35 + y, 254, 254, 254);
	PutPixel(34 + x, 35 + y, 255, 255, 255);
	PutPixel(37 + x, 35 + y, 255, 255, 255);
	PutPixel(38 + x, 35 + y, 255, 255, 255);
	PutPixel(39 + x, 35 + y, 255, 255, 255);
	PutPixel(40 + x, 35 + y, 255, 255, 255);
	PutPixel(41 + x, 35 + y, 255, 255, 255);
	PutPixel(42 + x, 35 + y, 255, 255, 255);
	PutPixel(43 + x, 35 + y, 254, 254, 254);
	PutPixel(44 + x, 35 + y, 255, 255, 255);
	PutPixel(2 + x, 36 + y, 255, 255, 255);
	PutPixel(3 + x, 36 + y, 255, 255, 255);
	PutPixel(4 + x, 36 + y, 255, 255, 255);
	PutPixel(10 + x, 36 + y, 255, 255, 255);
	PutPixel(11 + x, 36 + y, 255, 255, 255);
	PutPixel(12 + x, 36 + y, 255, 255, 255);
	PutPixel(13 + x, 36 + y, 254, 254, 254);
	PutPixel(17 + x, 36 + y, 254, 254, 254);
	PutPixel(18 + x, 36 + y, 255, 255, 255);
	PutPixel(19 + x, 36 + y, 254, 254, 254);
	PutPixel(20 + x, 36 + y, 255, 255, 255);
	PutPixel(21 + x, 36 + y, 255, 255, 255);
	PutPixel(22 + x, 36 + y, 255, 255, 255);
	PutPixel(23 + x, 36 + y, 255, 255, 255);
	PutPixel(27 + x, 36 + y, 254, 254, 254);
	PutPixel(28 + x, 36 + y, 255, 255, 255);
	PutPixel(29 + x, 36 + y, 255, 255, 255);
	PutPixel(37 + x, 36 + y, 255, 255, 255);
	PutPixel(38 + x, 36 + y, 255, 255, 255);
	PutPixel(39 + x, 36 + y, 254, 254, 254);
	PutPixel(40 + x, 36 + y, 254, 254, 254);
	PutPixel(41 + x, 36 + y, 255, 255, 255);
	PutPixel(42 + x, 36 + y, 255, 255, 255);
	PutPixel(43 + x, 36 + y, 255, 255, 255);
	PutPixel(44 + x, 36 + y, 254, 254, 254);
	PutPixel(2 + x, 37 + y, 254, 254, 254);
	PutPixel(3 + x, 37 + y, 255, 255, 255);
	PutPixel(4 + x, 37 + y, 255, 255, 255);
	PutPixel(5 + x, 37 + y, 255, 255, 255);
	PutPixel(10 + x, 37 + y, 254, 254, 254);
	PutPixel(11 + x, 37 + y, 255, 255, 255);
	PutPixel(12 + x, 37 + y, 255, 255, 255);
	PutPixel(13 + x, 37 + y, 255, 255, 255);
	PutPixel(17 + x, 37 + y, 255, 255, 255);
	PutPixel(18 + x, 37 + y, 255, 255, 255);
	PutPixel(19 + x, 37 + y, 255, 255, 255);
	PutPixel(20 + x, 37 + y, 254, 254, 254);
	PutPixel(21 + x, 37 + y, 255, 255, 255);
	PutPixel(22 + x, 37 + y, 255, 255, 255);
	PutPixel(23 + x, 37 + y, 255, 255, 255);
	PutPixel(27 + x, 37 + y, 254, 254, 254);
	PutPixel(28 + x, 37 + y, 255, 255, 255);
	PutPixel(29 + x, 37 + y, 255, 255, 255);
	PutPixel(37 + x, 37 + y, 255, 255, 255);
	PutPixel(38 + x, 37 + y, 255, 255, 255);
	PutPixel(39 + x, 37 + y, 254, 254, 254);
	PutPixel(42 + x, 37 + y, 255, 255, 255);
	PutPixel(43 + x, 37 + y, 255, 255, 255);
	PutPixel(44 + x, 37 + y, 255, 255, 255);
	PutPixel(45 + x, 37 + y, 255, 255, 255);
	PutPixel(2 + x, 38 + y, 255, 255, 255);
	PutPixel(3 + x, 38 + y, 255, 255, 255);
	PutPixel(4 + x, 38 + y, 255, 255, 255);
	PutPixel(5 + x, 38 + y, 254, 254, 254);
	PutPixel(6 + x, 38 + y, 255, 255, 255);
	PutPixel(9 + x, 38 + y, 255, 255, 255);
	PutPixel(10 + x, 38 + y, 255, 255, 255);
	PutPixel(11 + x, 38 + y, 255, 255, 255);
	PutPixel(12 + x, 38 + y, 254, 254, 254);
	PutPixel(17 + x, 38 + y, 254, 254, 254);
	PutPixel(18 + x, 38 + y, 255, 255, 255);
	PutPixel(19 + x, 38 + y, 255, 255, 255);
	PutPixel(20 + x, 38 + y, 254, 254, 254);
	PutPixel(21 + x, 38 + y, 255, 255, 255);
	PutPixel(22 + x, 38 + y, 254, 254, 254);
	PutPixel(27 + x, 38 + y, 254, 254, 254);
	PutPixel(28 + x, 38 + y, 255, 255, 255);
	PutPixel(29 + x, 38 + y, 255, 255, 255);
	PutPixel(37 + x, 38 + y, 255, 255, 255);
	PutPixel(38 + x, 38 + y, 255, 255, 255);
	PutPixel(39 + x, 38 + y, 254, 254, 254);
	PutPixel(42 + x, 38 + y, 254, 254, 254);
	PutPixel(43 + x, 38 + y, 255, 255, 255);
	PutPixel(44 + x, 38 + y, 255, 255, 255);
	PutPixel(45 + x, 38 + y, 255, 255, 255);
	PutPixel(3 + x, 39 + y, 254, 254, 254);
	PutPixel(4 + x, 39 + y, 255, 255, 255);
	PutPixel(5 + x, 39 + y, 255, 255, 255);
	PutPixel(6 + x, 39 + y, 255, 255, 255);
	PutPixel(7 + x, 39 + y, 254, 254, 254);
	PutPixel(8 + x, 39 + y, 255, 255, 255);
	PutPixel(9 + x, 39 + y, 255, 255, 255);
	PutPixel(10 + x, 39 + y, 255, 255, 255);
	PutPixel(11 + x, 39 + y, 255, 255, 255);
	PutPixel(12 + x, 39 + y, 254, 254, 254);
	PutPixel(17 + x, 39 + y, 255, 255, 255);
	PutPixel(18 + x, 39 + y, 255, 255, 255);
	PutPixel(19 + x, 39 + y, 255, 255, 255);
	PutPixel(20 + x, 39 + y, 255, 255, 255);
	PutPixel(21 + x, 39 + y, 255, 255, 255);
	PutPixel(22 + x, 39 + y, 254, 254, 254);
	PutPixel(27 + x, 39 + y, 254, 254, 254);
	PutPixel(28 + x, 39 + y, 255, 255, 255);
	PutPixel(29 + x, 39 + y, 255, 255, 255);
	PutPixel(30 + x, 39 + y, 254, 254, 254);
	PutPixel(31 + x, 39 + y, 254, 254, 254);
	PutPixel(32 + x, 39 + y, 254, 254, 254);
	PutPixel(33 + x, 39 + y, 254, 254, 254);
	PutPixel(34 + x, 39 + y, 254, 254, 254);
	PutPixel(37 + x, 39 + y, 255, 255, 255);
	PutPixel(38 + x, 39 + y, 255, 255, 255);
	PutPixel(39 + x, 39 + y, 254, 254, 254);
	PutPixel(42 + x, 39 + y, 255, 255, 255);
	PutPixel(43 + x, 39 + y, 255, 255, 255);
	PutPixel(44 + x, 39 + y, 255, 255, 255);
	PutPixel(45 + x, 39 + y, 255, 255, 255);
	PutPixel(3 + x, 40 + y, 255, 255, 255);
	PutPixel(4 + x, 40 + y, 255, 255, 255);
	PutPixel(5 + x, 40 + y, 255, 255, 255);
	PutPixel(6 + x, 40 + y, 255, 255, 255);
	PutPixel(7 + x, 40 + y, 255, 255, 255);
	PutPixel(8 + x, 40 + y, 255, 255, 255);
	PutPixel(9 + x, 40 + y, 255, 255, 255);
	PutPixel(10 + x, 40 + y, 255, 255, 255);
	PutPixel(11 + x, 40 + y, 254, 254, 254);
	PutPixel(18 + x, 40 + y, 254, 254, 254);
	PutPixel(19 + x, 40 + y, 255, 255, 255);
	PutPixel(20 + x, 40 + y, 255, 255, 255);
	PutPixel(21 + x, 40 + y, 255, 255, 255);
	PutPixel(22 + x, 40 + y, 255, 255, 255);
	PutPixel(27 + x, 40 + y, 254, 254, 254);
	PutPixel(28 + x, 40 + y, 255, 255, 255);
	PutPixel(29 + x, 40 + y, 255, 255, 255);
	PutPixel(30 + x, 40 + y, 255, 255, 255);
	PutPixel(31 + x, 40 + y, 255, 255, 255);
	PutPixel(32 + x, 40 + y, 255, 255, 255);
	PutPixel(33 + x, 40 + y, 255, 255, 255);
	PutPixel(34 + x, 40 + y, 255, 255, 255);
	PutPixel(37 + x, 40 + y, 255, 255, 255);
	PutPixel(38 + x, 40 + y, 255, 255, 255);
	PutPixel(39 + x, 40 + y, 254, 254, 254);
	PutPixel(42 + x, 40 + y, 255, 255, 255);
	PutPixel(43 + x, 40 + y, 255, 255, 255);
	PutPixel(44 + x, 40 + y, 255, 255, 255);
	PutPixel(45 + x, 40 + y, 255, 255, 255);
	PutPixel(4 + x, 41 + y, 255, 255, 255);
	PutPixel(5 + x, 41 + y, 254, 254, 254);
	PutPixel(6 + x, 41 + y, 254, 254, 254);
	PutPixel(7 + x, 41 + y, 255, 255, 255);
	PutPixel(8 + x, 41 + y, 255, 255, 255);
	PutPixel(9 + x, 41 + y, 255, 255, 255);
	PutPixel(10 + x, 41 + y, 255, 255, 255);
	PutPixel(18 + x, 41 + y, 254, 254, 254);
	PutPixel(19 + x, 41 + y, 255, 255, 255);
	PutPixel(20 + x, 41 + y, 255, 255, 255);
	PutPixel(21 + x, 41 + y, 254, 254, 254);
	PutPixel(27 + x, 41 + y, 254, 254, 254);
	PutPixel(28 + x, 41 + y, 255, 255, 255);
	PutPixel(29 + x, 41 + y, 255, 255, 255);
	PutPixel(30 + x, 41 + y, 255, 255, 255);
	PutPixel(31 + x, 41 + y, 255, 255, 255);
	PutPixel(32 + x, 41 + y, 255, 255, 255);
	PutPixel(33 + x, 41 + y, 255, 255, 255);
	PutPixel(34 + x, 41 + y, 255, 255, 255);
	PutPixel(37 + x, 41 + y, 255, 255, 255);
	PutPixel(38 + x, 41 + y, 255, 255, 255);
	PutPixel(39 + x, 41 + y, 254, 254, 254);
	PutPixel(43 + x, 41 + y, 255, 255, 255);
	PutPixel(44 + x, 41 + y, 255, 255, 255);
	PutPixel(45 + x, 41 + y, 255, 255, 255);
	PutPixel(46 + x, 41 + y, 255, 255, 255);

}

void Graphics::DrawStartGame(int x, int y)
{
	PutPixel(1 + x, 0 + y, 254, 254, 254);
	PutPixel(2 + x, 0 + y, 255, 255, 255);
	PutPixel(3 + x, 0 + y, 255, 255, 255);
	PutPixel(4 + x, 0 + y, 255, 255, 255);
	PutPixel(5 + x, 0 + y, 255, 255, 255);
	PutPixel(6 + x, 0 + y, 254, 254, 254);
	PutPixel(7 + x, 0 + y, 255, 255, 255);
	PutPixel(11 + x, 0 + y, 254, 254, 254);
	PutPixel(12 + x, 0 + y, 254, 254, 254);
	PutPixel(13 + x, 0 + y, 255, 255, 255);
	PutPixel(14 + x, 0 + y, 255, 255, 255);
	PutPixel(15 + x, 0 + y, 255, 255, 255);
	PutPixel(16 + x, 0 + y, 255, 255, 255);
	PutPixel(17 + x, 0 + y, 254, 254, 254);
	PutPixel(21 + x, 0 + y, 254, 254, 254);
	PutPixel(22 + x, 0 + y, 255, 255, 255);
	PutPixel(23 + x, 0 + y, 255, 255, 255);
	PutPixel(24 + x, 0 + y, 255, 255, 255);
	PutPixel(25 + x, 0 + y, 255, 255, 255);
	PutPixel(26 + x, 0 + y, 255, 255, 255);
	PutPixel(27 + x, 0 + y, 255, 255, 255);
	PutPixel(28 + x, 0 + y, 254, 254, 254);
	PutPixel(32 + x, 0 + y, 255, 255, 255);
	PutPixel(33 + x, 0 + y, 255, 255, 255);
	PutPixel(34 + x, 0 + y, 255, 255, 255);
	PutPixel(35 + x, 0 + y, 255, 255, 255);
	PutPixel(36 + x, 0 + y, 255, 255, 255);
	PutPixel(37 + x, 0 + y, 255, 255, 255);
	PutPixel(41 + x, 0 + y, 255, 255, 255);
	PutPixel(42 + x, 0 + y, 254, 254, 254);
	PutPixel(43 + x, 0 + y, 255, 255, 255);
	PutPixel(44 + x, 0 + y, 255, 255, 255);
	PutPixel(45 + x, 0 + y, 255, 255, 255);
	PutPixel(46 + x, 0 + y, 254, 254, 254);
	PutPixel(1 + x, 1 + y, 255, 255, 255);
	PutPixel(2 + x, 1 + y, 255, 255, 255);
	PutPixel(3 + x, 1 + y, 255, 255, 255);
	PutPixel(4 + x, 1 + y, 255, 255, 255);
	PutPixel(5 + x, 1 + y, 255, 255, 255);
	PutPixel(6 + x, 1 + y, 255, 255, 255);
	PutPixel(7 + x, 1 + y, 255, 255, 255);
	PutPixel(8 + x, 1 + y, 255, 255, 255);
	PutPixel(11 + x, 1 + y, 255, 255, 255);
	PutPixel(12 + x, 1 + y, 255, 255, 255);
	PutPixel(13 + x, 1 + y, 255, 255, 255);
	PutPixel(14 + x, 1 + y, 255, 255, 255);
	PutPixel(15 + x, 1 + y, 255, 255, 255);
	PutPixel(16 + x, 1 + y, 255, 255, 255);
	PutPixel(17 + x, 1 + y, 255, 255, 255);
	PutPixel(18 + x, 1 + y, 254, 254, 254);
	PutPixel(21 + x, 1 + y, 254, 254, 254);
	PutPixel(22 + x, 1 + y, 255, 255, 255);
	PutPixel(23 + x, 1 + y, 255, 255, 255);
	PutPixel(24 + x, 1 + y, 255, 255, 255);
	PutPixel(25 + x, 1 + y, 255, 255, 255);
	PutPixel(26 + x, 1 + y, 255, 255, 255);
	PutPixel(27 + x, 1 + y, 255, 255, 255);
	PutPixel(28 + x, 1 + y, 254, 254, 254);
	PutPixel(31 + x, 1 + y, 255, 255, 255);
	PutPixel(32 + x, 1 + y, 255, 255, 255);
	PutPixel(33 + x, 1 + y, 255, 255, 255);
	PutPixel(34 + x, 1 + y, 255, 255, 255);
	PutPixel(35 + x, 1 + y, 255, 255, 255);
	PutPixel(36 + x, 1 + y, 255, 255, 255);
	PutPixel(37 + x, 1 + y, 254, 254, 254);
	PutPixel(40 + x, 1 + y, 254, 254, 254);
	PutPixel(41 + x, 1 + y, 255, 255, 255);
	PutPixel(42 + x, 1 + y, 255, 255, 255);
	PutPixel(43 + x, 1 + y, 255, 255, 255);
	PutPixel(44 + x, 1 + y, 255, 255, 255);
	PutPixel(45 + x, 1 + y, 255, 255, 255);
	PutPixel(46 + x, 1 + y, 254, 254, 254);
	PutPixel(1 + x, 2 + y, 255, 255, 255);
	PutPixel(2 + x, 2 + y, 255, 255, 255);
	PutPixel(3 + x, 2 + y, 254, 254, 254);
	PutPixel(4 + x, 2 + y, 254, 254, 254);
	PutPixel(5 + x, 2 + y, 255, 255, 255);
	PutPixel(6 + x, 2 + y, 254, 254, 254);
	PutPixel(7 + x, 2 + y, 255, 255, 255);
	PutPixel(8 + x, 2 + y, 255, 255, 255);
	PutPixel(9 + x, 2 + y, 255, 255, 255);
	PutPixel(11 + x, 2 + y, 255, 255, 255);
	PutPixel(12 + x, 2 + y, 255, 255, 255);
	PutPixel(13 + x, 2 + y, 254, 254, 254);
	PutPixel(14 + x, 2 + y, 254, 254, 254);
	PutPixel(15 + x, 2 + y, 255, 255, 255);
	PutPixel(16 + x, 2 + y, 254, 254, 254);
	PutPixel(17 + x, 2 + y, 255, 255, 255);
	PutPixel(18 + x, 2 + y, 255, 255, 255);
	PutPixel(19 + x, 2 + y, 255, 255, 255);
	PutPixel(21 + x, 2 + y, 254, 254, 254);
	PutPixel(22 + x, 2 + y, 255, 255, 255);
	PutPixel(23 + x, 2 + y, 255, 255, 255);
	PutPixel(24 + x, 2 + y, 254, 254, 254);
	PutPixel(25 + x, 2 + y, 254, 254, 254);
	PutPixel(26 + x, 2 + y, 254, 254, 254);
	PutPixel(27 + x, 2 + y, 254, 254, 254);
	PutPixel(28 + x, 2 + y, 255, 255, 255);
	PutPixel(30 + x, 2 + y, 255, 255, 255);
	PutPixel(31 + x, 2 + y, 255, 255, 255);
	PutPixel(32 + x, 2 + y, 255, 255, 255);
	PutPixel(33 + x, 2 + y, 255, 255, 255);
	PutPixel(34 + x, 2 + y, 254, 254, 254);
	PutPixel(35 + x, 2 + y, 255, 255, 255);
	PutPixel(36 + x, 2 + y, 255, 255, 255);
	PutPixel(37 + x, 2 + y, 255, 255, 255);
	PutPixel(39 + x, 2 + y, 255, 255, 255);
	PutPixel(40 + x, 2 + y, 255, 255, 255);
	PutPixel(41 + x, 2 + y, 255, 255, 255);
	PutPixel(42 + x, 2 + y, 255, 255, 255);
	PutPixel(43 + x, 2 + y, 254, 254, 254);
	PutPixel(44 + x, 2 + y, 254, 254, 254);
	PutPixel(45 + x, 2 + y, 254, 254, 254);
	PutPixel(46 + x, 2 + y, 254, 254, 254);
	PutPixel(1 + x, 3 + y, 255, 255, 255);
	PutPixel(2 + x, 3 + y, 255, 255, 255);
	PutPixel(3 + x, 3 + y, 254, 254, 254);
	PutPixel(6 + x, 3 + y, 255, 255, 255);
	PutPixel(7 + x, 3 + y, 255, 255, 255);
	PutPixel(8 + x, 3 + y, 255, 255, 255);
	PutPixel(9 + x, 3 + y, 255, 255, 255);
	PutPixel(11 + x, 3 + y, 255, 255, 255);
	PutPixel(12 + x, 3 + y, 255, 255, 255);
	PutPixel(13 + x, 3 + y, 254, 254, 254);
	PutPixel(16 + x, 3 + y, 255, 255, 255);
	PutPixel(17 + x, 3 + y, 255, 255, 255);
	PutPixel(18 + x, 3 + y, 255, 255, 255);
	PutPixel(19 + x, 3 + y, 254, 254, 254);
	PutPixel(21 + x, 3 + y, 254, 254, 254);
	PutPixel(22 + x, 3 + y, 255, 255, 255);
	PutPixel(23 + x, 3 + y, 255, 255, 255);
	PutPixel(30 + x, 3 + y, 254, 254, 254);
	PutPixel(31 + x, 3 + y, 255, 255, 255);
	PutPixel(32 + x, 3 + y, 255, 255, 255);
	PutPixel(33 + x, 3 + y, 255, 255, 255);
	PutPixel(36 + x, 3 + y, 255, 255, 255);
	PutPixel(39 + x, 3 + y, 254, 254, 254);
	PutPixel(40 + x, 3 + y, 255, 255, 255);
	PutPixel(41 + x, 3 + y, 255, 255, 255);
	PutPixel(42 + x, 3 + y, 255, 255, 255);
	PutPixel(46 + x, 3 + y, 255, 255, 255);
	PutPixel(1 + x, 4 + y, 255, 255, 255);
	PutPixel(2 + x, 4 + y, 255, 255, 255);
	PutPixel(3 + x, 4 + y, 254, 254, 254);
	PutPixel(7 + x, 4 + y, 255, 255, 255);
	PutPixel(8 + x, 4 + y, 255, 255, 255);
	PutPixel(9 + x, 4 + y, 254, 254, 254);
	PutPixel(11 + x, 4 + y, 255, 255, 255);
	PutPixel(12 + x, 4 + y, 255, 255, 255);
	PutPixel(13 + x, 4 + y, 254, 254, 254);
	PutPixel(17 + x, 4 + y, 255, 255, 255);
	PutPixel(18 + x, 4 + y, 255, 255, 255);
	PutPixel(19 + x, 4 + y, 254, 254, 254);
	PutPixel(21 + x, 4 + y, 254, 254, 254);
	PutPixel(22 + x, 4 + y, 255, 255, 255);
	PutPixel(23 + x, 4 + y, 255, 255, 255);
	PutPixel(30 + x, 4 + y, 254, 254, 254);
	PutPixel(31 + x, 4 + y, 255, 255, 255);
	PutPixel(32 + x, 4 + y, 255, 255, 255);
	PutPixel(33 + x, 4 + y, 255, 255, 255);
	PutPixel(39 + x, 4 + y, 254, 254, 254);
	PutPixel(40 + x, 4 + y, 255, 255, 255);
	PutPixel(41 + x, 4 + y, 255, 255, 255);
	PutPixel(42 + x, 4 + y, 255, 255, 255);
	PutPixel(1 + x, 5 + y, 255, 255, 255);
	PutPixel(2 + x, 5 + y, 255, 255, 255);
	PutPixel(3 + x, 5 + y, 254, 254, 254);
	PutPixel(6 + x, 5 + y, 255, 255, 255);
	PutPixel(7 + x, 5 + y, 255, 255, 255);
	PutPixel(8 + x, 5 + y, 255, 255, 255);
	PutPixel(9 + x, 5 + y, 254, 254, 254);
	PutPixel(11 + x, 5 + y, 255, 255, 255);
	PutPixel(12 + x, 5 + y, 255, 255, 255);
	PutPixel(13 + x, 5 + y, 254, 254, 254);
	PutPixel(16 + x, 5 + y, 255, 255, 255);
	PutPixel(17 + x, 5 + y, 255, 255, 255);
	PutPixel(18 + x, 5 + y, 255, 255, 255);
	PutPixel(19 + x, 5 + y, 255, 255, 255);
	PutPixel(21 + x, 5 + y, 254, 254, 254);
	PutPixel(22 + x, 5 + y, 255, 255, 255);
	PutPixel(23 + x, 5 + y, 255, 255, 255);
	PutPixel(30 + x, 5 + y, 255, 255, 255);
	PutPixel(31 + x, 5 + y, 255, 255, 255);
	PutPixel(32 + x, 5 + y, 255, 255, 255);
	PutPixel(33 + x, 5 + y, 255, 255, 255);
	PutPixel(34 + x, 5 + y, 255, 255, 255);
	PutPixel(39 + x, 5 + y, 255, 255, 255);
	PutPixel(40 + x, 5 + y, 255, 255, 255);
	PutPixel(41 + x, 5 + y, 255, 255, 255);
	PutPixel(42 + x, 5 + y, 255, 255, 255);
	PutPixel(43 + x, 5 + y, 255, 255, 255);
	PutPixel(1 + x, 6 + y, 255, 255, 255);
	PutPixel(2 + x, 6 + y, 255, 255, 255);
	PutPixel(3 + x, 6 + y, 254, 254, 254);
	PutPixel(6 + x, 6 + y, 254, 254, 254);
	PutPixel(7 + x, 6 + y, 255, 255, 255);
	PutPixel(8 + x, 6 + y, 255, 255, 255);
	PutPixel(9 + x, 6 + y, 255, 255, 255);
	PutPixel(11 + x, 6 + y, 255, 255, 255);
	PutPixel(12 + x, 6 + y, 255, 255, 255);
	PutPixel(13 + x, 6 + y, 254, 254, 254);
	PutPixel(15 + x, 6 + y, 255, 255, 255);
	PutPixel(16 + x, 6 + y, 254, 254, 254);
	PutPixel(17 + x, 6 + y, 255, 255, 255);
	PutPixel(18 + x, 6 + y, 255, 255, 255);
	PutPixel(19 + x, 6 + y, 255, 255, 255);
	PutPixel(21 + x, 6 + y, 254, 254, 254);
	PutPixel(22 + x, 6 + y, 255, 255, 255);
	PutPixel(23 + x, 6 + y, 255, 255, 255);
	PutPixel(24 + x, 6 + y, 255, 255, 255);
	PutPixel(25 + x, 6 + y, 255, 255, 255);
	PutPixel(26 + x, 6 + y, 255, 255, 255);
	PutPixel(27 + x, 6 + y, 255, 255, 255);
	PutPixel(28 + x, 6 + y, 255, 255, 255);
	PutPixel(30 + x, 6 + y, 255, 255, 255);
	PutPixel(31 + x, 6 + y, 254, 254, 254);
	PutPixel(32 + x, 6 + y, 255, 255, 255);
	PutPixel(33 + x, 6 + y, 255, 255, 255);
	PutPixel(34 + x, 6 + y, 255, 255, 255);
	PutPixel(35 + x, 6 + y, 254, 254, 254);
	PutPixel(36 + x, 6 + y, 255, 255, 255);
	PutPixel(39 + x, 6 + y, 255, 255, 255);
	PutPixel(40 + x, 6 + y, 254, 254, 254);
	PutPixel(41 + x, 6 + y, 255, 255, 255);
	PutPixel(42 + x, 6 + y, 255, 255, 255);
	PutPixel(43 + x, 6 + y, 255, 255, 255);
	PutPixel(44 + x, 6 + y, 254, 254, 254);
	PutPixel(45 + x, 6 + y, 255, 255, 255);
	PutPixel(1 + x, 7 + y, 255, 255, 255);
	PutPixel(2 + x, 7 + y, 255, 255, 255);
	PutPixel(3 + x, 7 + y, 254, 254, 254);
	PutPixel(4 + x, 7 + y, 254, 254, 254);
	PutPixel(5 + x, 7 + y, 254, 254, 254);
	PutPixel(6 + x, 7 + y, 255, 255, 255);
	PutPixel(7 + x, 7 + y, 255, 255, 255);
	PutPixel(8 + x, 7 + y, 254, 254, 254);
	PutPixel(9 + x, 7 + y, 255, 255, 255);
	PutPixel(11 + x, 7 + y, 255, 255, 255);
	PutPixel(12 + x, 7 + y, 255, 255, 255);
	PutPixel(13 + x, 7 + y, 255, 255, 255);
	PutPixel(14 + x, 7 + y, 255, 255, 255);
	PutPixel(15 + x, 7 + y, 255, 255, 255);
	PutPixel(16 + x, 7 + y, 255, 255, 255);
	PutPixel(17 + x, 7 + y, 255, 255, 255);
	PutPixel(18 + x, 7 + y, 255, 255, 255);
	PutPixel(21 + x, 7 + y, 254, 254, 254);
	PutPixel(22 + x, 7 + y, 255, 255, 255);
	PutPixel(23 + x, 7 + y, 255, 255, 255);
	PutPixel(24 + x, 7 + y, 255, 255, 255);
	PutPixel(25 + x, 7 + y, 255, 255, 255);
	PutPixel(26 + x, 7 + y, 255, 255, 255);
	PutPixel(27 + x, 7 + y, 255, 255, 255);
	PutPixel(28 + x, 7 + y, 255, 255, 255);
	PutPixel(31 + x, 7 + y, 255, 255, 255);
	PutPixel(32 + x, 7 + y, 254, 254, 254);
	PutPixel(33 + x, 7 + y, 255, 255, 255);
	PutPixel(34 + x, 7 + y, 255, 255, 255);
	PutPixel(35 + x, 7 + y, 255, 255, 255);
	PutPixel(36 + x, 7 + y, 254, 254, 254);
	PutPixel(37 + x, 7 + y, 255, 255, 255);
	PutPixel(40 + x, 7 + y, 255, 255, 255);
	PutPixel(41 + x, 7 + y, 254, 254, 254);
	PutPixel(42 + x, 7 + y, 255, 255, 255);
	PutPixel(43 + x, 7 + y, 255, 255, 255);
	PutPixel(44 + x, 7 + y, 255, 255, 255);
	PutPixel(45 + x, 7 + y, 255, 255, 255);
	PutPixel(46 + x, 7 + y, 255, 255, 255);
	PutPixel(1 + x, 8 + y, 255, 255, 255);
	PutPixel(2 + x, 8 + y, 255, 255, 255);
	PutPixel(3 + x, 8 + y, 255, 255, 255);
	PutPixel(4 + x, 8 + y, 255, 255, 255);
	PutPixel(5 + x, 8 + y, 255, 255, 255);
	PutPixel(6 + x, 8 + y, 255, 255, 255);
	PutPixel(7 + x, 8 + y, 255, 255, 255);
	PutPixel(8 + x, 8 + y, 255, 255, 255);
	PutPixel(11 + x, 8 + y, 255, 255, 255);
	PutPixel(12 + x, 8 + y, 255, 255, 255);
	PutPixel(13 + x, 8 + y, 255, 255, 255);
	PutPixel(14 + x, 8 + y, 255, 255, 255);
	PutPixel(15 + x, 8 + y, 255, 255, 255);
	PutPixel(16 + x, 8 + y, 255, 255, 255);
	PutPixel(17 + x, 8 + y, 255, 255, 255);
	PutPixel(18 + x, 8 + y, 255, 255, 255);
	PutPixel(21 + x, 8 + y, 254, 254, 254);
	PutPixel(22 + x, 8 + y, 255, 255, 255);
	PutPixel(23 + x, 8 + y, 255, 255, 255);
	PutPixel(24 + x, 8 + y, 254, 254, 254);
	PutPixel(25 + x, 8 + y, 254, 254, 254);
	PutPixel(26 + x, 8 + y, 254, 254, 254);
	PutPixel(27 + x, 8 + y, 254, 254, 254);
	PutPixel(28 + x, 8 + y, 255, 255, 255);
	PutPixel(32 + x, 8 + y, 255, 255, 255);
	PutPixel(33 + x, 8 + y, 254, 254, 254);
	PutPixel(34 + x, 8 + y, 255, 255, 255);
	PutPixel(35 + x, 8 + y, 255, 255, 255);
	PutPixel(36 + x, 8 + y, 255, 255, 255);
	PutPixel(37 + x, 8 + y, 254, 254, 254);
	PutPixel(41 + x, 8 + y, 255, 255, 255);
	PutPixel(42 + x, 8 + y, 254, 254, 254);
	PutPixel(43 + x, 8 + y, 254, 254, 254);
	PutPixel(44 + x, 8 + y, 255, 255, 255);
	PutPixel(45 + x, 8 + y, 255, 255, 255);
	PutPixel(46 + x, 8 + y, 255, 255, 255);
	PutPixel(47 + x, 8 + y, 255, 255, 255);
	PutPixel(1 + x, 9 + y, 255, 255, 255);
	PutPixel(2 + x, 9 + y, 255, 255, 255);
	PutPixel(3 + x, 9 + y, 255, 255, 255);
	PutPixel(4 + x, 9 + y, 255, 255, 255);
	PutPixel(5 + x, 9 + y, 254, 254, 254);
	PutPixel(6 + x, 9 + y, 255, 255, 255);
	PutPixel(7 + x, 9 + y, 255, 255, 255);
	PutPixel(11 + x, 9 + y, 255, 255, 255);
	PutPixel(12 + x, 9 + y, 255, 255, 255);
	PutPixel(13 + x, 9 + y, 254, 254, 254);
	PutPixel(14 + x, 9 + y, 254, 254, 254);
	PutPixel(15 + x, 9 + y, 254, 254, 254);
	PutPixel(16 + x, 9 + y, 255, 255, 255);
	PutPixel(17 + x, 9 + y, 255, 255, 255);
	PutPixel(18 + x, 9 + y, 254, 254, 254);
	PutPixel(21 + x, 9 + y, 254, 254, 254);
	PutPixel(22 + x, 9 + y, 255, 255, 255);
	PutPixel(23 + x, 9 + y, 255, 255, 255);
	PutPixel(34 + x, 9 + y, 255, 255, 255);
	PutPixel(35 + x, 9 + y, 254, 254, 254);
	PutPixel(36 + x, 9 + y, 255, 255, 255);
	PutPixel(37 + x, 9 + y, 254, 254, 254);
	PutPixel(43 + x, 9 + y, 255, 255, 255);
	PutPixel(44 + x, 9 + y, 254, 254, 254);
	PutPixel(45 + x, 9 + y, 255, 255, 255);
	PutPixel(46 + x, 9 + y, 255, 255, 255);
	PutPixel(47 + x, 9 + y, 255, 255, 255);
	PutPixel(1 + x, 10 + y, 255, 255, 255);
	PutPixel(2 + x, 10 + y, 255, 255, 255);
	PutPixel(3 + x, 10 + y, 254, 254, 254);
	PutPixel(11 + x, 10 + y, 255, 255, 255);
	PutPixel(12 + x, 10 + y, 255, 255, 255);
	PutPixel(13 + x, 10 + y, 254, 254, 254);
	PutPixel(16 + x, 10 + y, 254, 254, 254);
	PutPixel(17 + x, 10 + y, 255, 255, 255);
	PutPixel(18 + x, 10 + y, 254, 254, 254);
	PutPixel(21 + x, 10 + y, 254, 254, 254);
	PutPixel(22 + x, 10 + y, 255, 255, 255);
	PutPixel(23 + x, 10 + y, 255, 255, 255);
	PutPixel(35 + x, 10 + y, 254, 254, 254);
	PutPixel(36 + x, 10 + y, 255, 255, 255);
	PutPixel(37 + x, 10 + y, 255, 255, 255);
	PutPixel(45 + x, 10 + y, 255, 255, 255);
	PutPixel(46 + x, 10 + y, 255, 255, 255);
	PutPixel(47 + x, 10 + y, 254, 254, 254);
	PutPixel(1 + x, 11 + y, 255, 255, 255);
	PutPixel(2 + x, 11 + y, 255, 255, 255);
	PutPixel(3 + x, 11 + y, 254, 254, 254);
	PutPixel(11 + x, 11 + y, 255, 255, 255);
	PutPixel(12 + x, 11 + y, 255, 255, 255);
	PutPixel(13 + x, 11 + y, 254, 254, 254);
	PutPixel(16 + x, 11 + y, 255, 255, 255);
	PutPixel(17 + x, 11 + y, 255, 255, 255);
	PutPixel(18 + x, 11 + y, 255, 255, 255);
	PutPixel(19 + x, 11 + y, 255, 255, 255);
	PutPixel(21 + x, 11 + y, 254, 254, 254);
	PutPixel(22 + x, 11 + y, 255, 255, 255);
	PutPixel(23 + x, 11 + y, 255, 255, 255);
	PutPixel(30 + x, 11 + y, 255, 255, 255);
	PutPixel(31 + x, 11 + y, 255, 255, 255);
	PutPixel(35 + x, 11 + y, 255, 255, 255);
	PutPixel(36 + x, 11 + y, 255, 255, 255);
	PutPixel(37 + x, 11 + y, 254, 254, 254);
	PutPixel(39 + x, 11 + y, 255, 255, 255);
	PutPixel(40 + x, 11 + y, 255, 255, 255);
	PutPixel(44 + x, 11 + y, 255, 255, 255);
	PutPixel(45 + x, 11 + y, 255, 255, 255);
	PutPixel(46 + x, 11 + y, 255, 255, 255);
	PutPixel(47 + x, 11 + y, 255, 255, 255);
	PutPixel(1 + x, 12 + y, 255, 255, 255);
	PutPixel(2 + x, 12 + y, 255, 255, 255);
	PutPixel(3 + x, 12 + y, 254, 254, 254);
	PutPixel(11 + x, 12 + y, 255, 255, 255);
	PutPixel(12 + x, 12 + y, 255, 255, 255);
	PutPixel(13 + x, 12 + y, 254, 254, 254);
	PutPixel(16 + x, 12 + y, 255, 255, 255);
	PutPixel(17 + x, 12 + y, 255, 255, 255);
	PutPixel(18 + x, 12 + y, 255, 255, 255);
	PutPixel(19 + x, 12 + y, 255, 255, 255);
	PutPixel(21 + x, 12 + y, 254, 254, 254);
	PutPixel(22 + x, 12 + y, 255, 255, 255);
	PutPixel(23 + x, 12 + y, 255, 255, 255);
	PutPixel(24 + x, 12 + y, 254, 254, 254);
	PutPixel(25 + x, 12 + y, 254, 254, 254);
	PutPixel(26 + x, 12 + y, 254, 254, 254);
	PutPixel(27 + x, 12 + y, 254, 254, 254);
	PutPixel(28 + x, 12 + y, 255, 255, 255);
	PutPixel(30 + x, 12 + y, 255, 255, 255);
	PutPixel(31 + x, 12 + y, 255, 255, 255);
	PutPixel(32 + x, 12 + y, 254, 254, 254);
	PutPixel(33 + x, 12 + y, 254, 254, 254);
	PutPixel(34 + x, 12 + y, 254, 254, 254);
	PutPixel(35 + x, 12 + y, 255, 255, 255);
	PutPixel(36 + x, 12 + y, 255, 255, 255);
	PutPixel(37 + x, 12 + y, 254, 254, 254);
	PutPixel(39 + x, 12 + y, 255, 255, 255);
	PutPixel(40 + x, 12 + y, 255, 255, 255);
	PutPixel(41 + x, 12 + y, 254, 254, 254);
	PutPixel(42 + x, 12 + y, 254, 254, 254);
	PutPixel(43 + x, 12 + y, 255, 255, 255);
	PutPixel(44 + x, 12 + y, 255, 255, 255);
	PutPixel(45 + x, 12 + y, 255, 255, 255);
	PutPixel(46 + x, 12 + y, 255, 255, 255);
	PutPixel(47 + x, 12 + y, 255, 255, 255);
	PutPixel(1 + x, 13 + y, 255, 255, 255);
	PutPixel(2 + x, 13 + y, 255, 255, 255);
	PutPixel(3 + x, 13 + y, 254, 254, 254);
	PutPixel(11 + x, 13 + y, 255, 255, 255);
	PutPixel(12 + x, 13 + y, 255, 255, 255);
	PutPixel(13 + x, 13 + y, 254, 254, 254);
	PutPixel(16 + x, 13 + y, 255, 255, 255);
	PutPixel(17 + x, 13 + y, 255, 255, 255);
	PutPixel(18 + x, 13 + y, 255, 255, 255);
	PutPixel(19 + x, 13 + y, 255, 255, 255);
	PutPixel(21 + x, 13 + y, 254, 254, 254);
	PutPixel(22 + x, 13 + y, 255, 255, 255);
	PutPixel(23 + x, 13 + y, 255, 255, 255);
	PutPixel(24 + x, 13 + y, 255, 255, 255);
	PutPixel(25 + x, 13 + y, 255, 255, 255);
	PutPixel(26 + x, 13 + y, 255, 255, 255);
	PutPixel(27 + x, 13 + y, 255, 255, 255);
	PutPixel(28 + x, 13 + y, 254, 254, 254);
	PutPixel(30 + x, 13 + y, 254, 254, 254);
	PutPixel(31 + x, 13 + y, 255, 255, 255);
	PutPixel(32 + x, 13 + y, 255, 255, 255);
	PutPixel(33 + x, 13 + y, 255, 255, 255);
	PutPixel(34 + x, 13 + y, 255, 255, 255);
	PutPixel(35 + x, 13 + y, 255, 255, 255);
	PutPixel(36 + x, 13 + y, 254, 254, 254);
	PutPixel(37 + x, 13 + y, 255, 255, 255);
	PutPixel(39 + x, 13 + y, 254, 254, 254);
	PutPixel(40 + x, 13 + y, 255, 255, 255);
	PutPixel(41 + x, 13 + y, 255, 255, 255);
	PutPixel(42 + x, 13 + y, 255, 255, 255);
	PutPixel(43 + x, 13 + y, 255, 255, 255);
	PutPixel(44 + x, 13 + y, 255, 255, 255);
	PutPixel(45 + x, 13 + y, 255, 255, 255);
	PutPixel(46 + x, 13 + y, 255, 255, 255);
	PutPixel(1 + x, 14 + y, 255, 255, 255);
	PutPixel(2 + x, 14 + y, 255, 255, 255);
	PutPixel(3 + x, 14 + y, 254, 254, 254);
	PutPixel(11 + x, 14 + y, 255, 255, 255);
	PutPixel(12 + x, 14 + y, 255, 255, 255);
	PutPixel(13 + x, 14 + y, 254, 254, 254);
	PutPixel(17 + x, 14 + y, 255, 255, 255);
	PutPixel(18 + x, 14 + y, 255, 255, 255);
	PutPixel(19 + x, 14 + y, 255, 255, 255);
	PutPixel(21 + x, 14 + y, 254, 254, 254);
	PutPixel(22 + x, 14 + y, 255, 255, 255);
	PutPixel(23 + x, 14 + y, 255, 255, 255);
	PutPixel(24 + x, 14 + y, 255, 255, 255);
	PutPixel(25 + x, 14 + y, 255, 255, 255);
	PutPixel(26 + x, 14 + y, 255, 255, 255);
	PutPixel(27 + x, 14 + y, 255, 255, 255);
	PutPixel(28 + x, 14 + y, 254, 254, 254);
	PutPixel(30 + x, 14 + y, 255, 255, 255);
	PutPixel(31 + x, 14 + y, 254, 254, 254);
	PutPixel(32 + x, 14 + y, 254, 254, 254);
	PutPixel(33 + x, 14 + y, 255, 255, 255);
	PutPixel(34 + x, 14 + y, 254, 254, 254);
	PutPixel(35 + x, 14 + y, 254, 254, 254);
	PutPixel(36 + x, 14 + y, 255, 255, 255);
	PutPixel(39 + x, 14 + y, 255, 255, 255);
	PutPixel(40 + x, 14 + y, 254, 254, 254);
	PutPixel(41 + x, 14 + y, 254, 254, 254);
	PutPixel(42 + x, 14 + y, 255, 255, 255);
	PutPixel(43 + x, 14 + y, 255, 255, 255);
	PutPixel(44 + x, 14 + y, 255, 255, 255);
	PutPixel(45 + x, 14 + y, 255, 255, 255);
	PutPixel(0 + x, 27 + y, 255, 255, 255);
	PutPixel(1 + x, 27 + y, 255, 255, 255);
	PutPixel(2 + x, 27 + y, 255, 255, 255);
	PutPixel(3 + x, 27 + y, 255, 255, 255);
	PutPixel(4 + x, 27 + y, 255, 255, 255);
	PutPixel(5 + x, 27 + y, 255, 255, 255);
	PutPixel(6 + x, 27 + y, 255, 255, 255);
	PutPixel(9 + x, 27 + y, 254, 254, 254);
	PutPixel(10 + x, 27 + y, 255, 255, 255);
	PutPixel(11 + x, 27 + y, 255, 255, 255);
	PutPixel(12 + x, 27 + y, 255, 255, 255);
	PutPixel(16 + x, 27 + y, 254, 254, 254);
	PutPixel(17 + x, 27 + y, 255, 255, 255);
	PutPixel(18 + x, 27 + y, 255, 255, 255);
	PutPixel(20 + x, 27 + y, 254, 254, 254);
	PutPixel(21 + x, 27 + y, 255, 255, 255);
	PutPixel(22 + x, 27 + y, 255, 255, 255);
	PutPixel(23 + x, 27 + y, 255, 255, 255);
	PutPixel(24 + x, 27 + y, 255, 255, 255);
	PutPixel(25 + x, 27 + y, 255, 255, 255);
	PutPixel(26 + x, 27 + y, 255, 255, 255);
	PutPixel(27 + x, 27 + y, 255, 255, 255);
	PutPixel(28 + x, 27 + y, 255, 255, 255);
	PutPixel(29 + x, 27 + y, 255, 255, 255);
	PutPixel(30 + x, 27 + y, 254, 254, 254);
	PutPixel(31 + x, 27 + y, 255, 255, 255);
	PutPixel(32 + x, 27 + y, 255, 255, 255);
	PutPixel(33 + x, 27 + y, 255, 255, 255);
	PutPixel(34 + x, 27 + y, 255, 255, 255);
	PutPixel(35 + x, 27 + y, 255, 255, 255);
	PutPixel(36 + x, 27 + y, 255, 255, 255);
	PutPixel(37 + x, 27 + y, 254, 254, 254);
	PutPixel(40 + x, 27 + y, 254, 254, 254);
	PutPixel(41 + x, 27 + y, 254, 254, 254);
	PutPixel(42 + x, 27 + y, 255, 255, 255);
	PutPixel(43 + x, 27 + y, 255, 255, 255);
	PutPixel(44 + x, 27 + y, 254, 254, 254);
	PutPixel(45 + x, 27 + y, 255, 255, 255);
	PutPixel(46 + x, 27 + y, 255, 255, 255);
	PutPixel(0 + x, 28 + y, 255, 255, 255);
	PutPixel(1 + x, 28 + y, 255, 255, 255);
	PutPixel(2 + x, 28 + y, 255, 255, 255);
	PutPixel(3 + x, 28 + y, 255, 255, 255);
	PutPixel(4 + x, 28 + y, 255, 255, 255);
	PutPixel(5 + x, 28 + y, 255, 255, 255);
	PutPixel(6 + x, 28 + y, 255, 255, 255);
	PutPixel(9 + x, 28 + y, 254, 254, 254);
	PutPixel(10 + x, 28 + y, 255, 255, 255);
	PutPixel(11 + x, 28 + y, 255, 255, 255);
	PutPixel(12 + x, 28 + y, 255, 255, 255);
	PutPixel(13 + x, 28 + y, 255, 255, 255);
	PutPixel(16 + x, 28 + y, 254, 254, 254);
	PutPixel(17 + x, 28 + y, 255, 255, 255);
	PutPixel(18 + x, 28 + y, 255, 255, 255);
	PutPixel(20 + x, 28 + y, 254, 254, 254);
	PutPixel(21 + x, 28 + y, 255, 255, 255);
	PutPixel(22 + x, 28 + y, 255, 255, 255);
	PutPixel(23 + x, 28 + y, 255, 255, 255);
	PutPixel(24 + x, 28 + y, 255, 255, 255);
	PutPixel(25 + x, 28 + y, 255, 255, 255);
	PutPixel(26 + x, 28 + y, 255, 255, 255);
	PutPixel(27 + x, 28 + y, 255, 255, 255);
	PutPixel(28 + x, 28 + y, 255, 255, 255);
	PutPixel(29 + x, 28 + y, 255, 255, 255);
	PutPixel(30 + x, 28 + y, 254, 254, 254);
	PutPixel(31 + x, 28 + y, 255, 255, 255);
	PutPixel(32 + x, 28 + y, 255, 255, 255);
	PutPixel(33 + x, 28 + y, 255, 255, 255);
	PutPixel(34 + x, 28 + y, 255, 255, 255);
	PutPixel(35 + x, 28 + y, 255, 255, 255);
	PutPixel(36 + x, 28 + y, 255, 255, 255);
	PutPixel(37 + x, 28 + y, 254, 254, 254);
	PutPixel(40 + x, 28 + y, 255, 255, 255);
	PutPixel(41 + x, 28 + y, 255, 255, 255);
	PutPixel(42 + x, 28 + y, 255, 255, 255);
	PutPixel(43 + x, 28 + y, 255, 255, 255);
	PutPixel(44 + x, 28 + y, 255, 255, 255);
	PutPixel(45 + x, 28 + y, 255, 255, 255);
	PutPixel(46 + x, 28 + y, 255, 255, 255);
	PutPixel(47 + x, 28 + y, 255, 255, 255);
	PutPixel(0 + x, 29 + y, 255, 255, 255);
	PutPixel(1 + x, 29 + y, 255, 255, 255);
	PutPixel(2 + x, 29 + y, 254, 254, 254);
	PutPixel(3 + x, 29 + y, 254, 254, 254);
	PutPixel(4 + x, 29 + y, 254, 254, 254);
	PutPixel(5 + x, 29 + y, 254, 254, 254);
	PutPixel(6 + x, 29 + y, 254, 254, 254);
	PutPixel(9 + x, 29 + y, 254, 254, 254);
	PutPixel(10 + x, 29 + y, 255, 255, 255);
	PutPixel(11 + x, 29 + y, 255, 255, 255);
	PutPixel(12 + x, 29 + y, 255, 255, 255);
	PutPixel(13 + x, 29 + y, 254, 254, 254);
	PutPixel(16 + x, 29 + y, 254, 254, 254);
	PutPixel(17 + x, 29 + y, 255, 255, 255);
	PutPixel(18 + x, 29 + y, 255, 255, 255);
	PutPixel(20 + x, 29 + y, 255, 255, 255);
	PutPixel(21 + x, 29 + y, 254, 254, 254);
	PutPixel(22 + x, 29 + y, 254, 254, 254);
	PutPixel(23 + x, 29 + y, 254, 254, 254);
	PutPixel(24 + x, 29 + y, 255, 255, 255);
	PutPixel(25 + x, 29 + y, 255, 255, 255);
	PutPixel(26 + x, 29 + y, 254, 254, 254);
	PutPixel(27 + x, 29 + y, 254, 254, 254);
	PutPixel(28 + x, 29 + y, 254, 254, 254);
	PutPixel(29 + x, 29 + y, 255, 255, 255);
	PutPixel(30 + x, 29 + y, 254, 254, 254);
	PutPixel(31 + x, 29 + y, 255, 255, 255);
	PutPixel(32 + x, 29 + y, 255, 255, 255);
	PutPixel(33 + x, 29 + y, 254, 254, 254);
	PutPixel(34 + x, 29 + y, 254, 254, 254);
	PutPixel(35 + x, 29 + y, 254, 254, 254);
	PutPixel(36 + x, 29 + y, 254, 254, 254);
	PutPixel(37 + x, 29 + y, 255, 255, 255);
	PutPixel(40 + x, 29 + y, 255, 255, 255);
	PutPixel(41 + x, 29 + y, 255, 255, 255);
	PutPixel(42 + x, 29 + y, 254, 254, 254);
	PutPixel(43 + x, 29 + y, 254, 254, 254);
	PutPixel(44 + x, 29 + y, 255, 255, 255);
	PutPixel(45 + x, 29 + y, 255, 255, 255);
	PutPixel(46 + x, 29 + y, 255, 255, 255);
	PutPixel(47 + x, 29 + y, 255, 255, 255);
	PutPixel(0 + x, 30 + y, 255, 255, 255);
	PutPixel(1 + x, 30 + y, 255, 255, 255);
	PutPixel(2 + x, 30 + y, 254, 254, 254);
	PutPixel(9 + x, 30 + y, 254, 254, 254);
	PutPixel(10 + x, 30 + y, 255, 255, 255);
	PutPixel(11 + x, 30 + y, 255, 255, 255);
	PutPixel(12 + x, 30 + y, 255, 255, 255);
	PutPixel(13 + x, 30 + y, 255, 255, 255);
	PutPixel(14 + x, 30 + y, 255, 255, 255);
	PutPixel(16 + x, 30 + y, 254, 254, 254);
	PutPixel(17 + x, 30 + y, 255, 255, 255);
	PutPixel(18 + x, 30 + y, 255, 255, 255);
	PutPixel(23 + x, 30 + y, 254, 254, 254);
	PutPixel(24 + x, 30 + y, 255, 255, 255);
	PutPixel(25 + x, 30 + y, 255, 255, 255);
	PutPixel(30 + x, 30 + y, 254, 254, 254);
	PutPixel(31 + x, 30 + y, 255, 255, 255);
	PutPixel(32 + x, 30 + y, 255, 255, 255);
	PutPixel(40 + x, 30 + y, 255, 255, 255);
	PutPixel(41 + x, 30 + y, 255, 255, 255);
	PutPixel(42 + x, 30 + y, 254, 254, 254);
	PutPixel(45 + x, 30 + y, 254, 254, 254);
	PutPixel(46 + x, 30 + y, 255, 255, 255);
	PutPixel(47 + x, 30 + y, 254, 254, 254);
	PutPixel(0 + x, 31 + y, 255, 255, 255);
	PutPixel(1 + x, 31 + y, 255, 255, 255);
	PutPixel(2 + x, 31 + y, 254, 254, 254);
	PutPixel(9 + x, 31 + y, 254, 254, 254);
	PutPixel(10 + x, 31 + y, 255, 255, 255);
	PutPixel(11 + x, 31 + y, 254, 254, 254);
	PutPixel(12 + x, 31 + y, 254, 254, 254);
	PutPixel(13 + x, 31 + y, 255, 255, 255);
	PutPixel(14 + x, 31 + y, 254, 254, 254);
	PutPixel(16 + x, 31 + y, 254, 254, 254);
	PutPixel(17 + x, 31 + y, 255, 255, 255);
	PutPixel(18 + x, 31 + y, 255, 255, 255);
	PutPixel(23 + x, 31 + y, 254, 254, 254);
	PutPixel(24 + x, 31 + y, 255, 255, 255);
	PutPixel(25 + x, 31 + y, 255, 255, 255);
	PutPixel(30 + x, 31 + y, 254, 254, 254);
	PutPixel(31 + x, 31 + y, 255, 255, 255);
	PutPixel(32 + x, 31 + y, 255, 255, 255);
	PutPixel(40 + x, 31 + y, 255, 255, 255);
	PutPixel(41 + x, 31 + y, 255, 255, 255);
	PutPixel(42 + x, 31 + y, 254, 254, 254);
	PutPixel(45 + x, 31 + y, 254, 254, 254);
	PutPixel(46 + x, 31 + y, 255, 255, 255);
	PutPixel(47 + x, 31 + y, 255, 255, 255);
	PutPixel(0 + x, 32 + y, 255, 255, 255);
	PutPixel(1 + x, 32 + y, 255, 255, 255);
	PutPixel(2 + x, 32 + y, 254, 254, 254);
	PutPixel(9 + x, 32 + y, 254, 254, 254);
	PutPixel(10 + x, 32 + y, 255, 255, 255);
	PutPixel(11 + x, 32 + y, 255, 255, 255);
	PutPixel(12 + x, 32 + y, 255, 255, 255);
	PutPixel(13 + x, 32 + y, 255, 255, 255);
	PutPixel(14 + x, 32 + y, 254, 254, 254);
	PutPixel(16 + x, 32 + y, 254, 254, 254);
	PutPixel(17 + x, 32 + y, 255, 255, 255);
	PutPixel(18 + x, 32 + y, 255, 255, 255);
	PutPixel(23 + x, 32 + y, 254, 254, 254);
	PutPixel(24 + x, 32 + y, 255, 255, 255);
	PutPixel(25 + x, 32 + y, 255, 255, 255);
	PutPixel(30 + x, 32 + y, 254, 254, 254);
	PutPixel(31 + x, 32 + y, 255, 255, 255);
	PutPixel(32 + x, 32 + y, 255, 255, 255);
	PutPixel(40 + x, 32 + y, 255, 255, 255);
	PutPixel(41 + x, 32 + y, 255, 255, 255);
	PutPixel(42 + x, 32 + y, 254, 254, 254);
	PutPixel(45 + x, 32 + y, 255, 255, 255);
	PutPixel(46 + x, 32 + y, 255, 255, 255);
	PutPixel(47 + x, 32 + y, 254, 254, 254);
	PutPixel(0 + x, 33 + y, 255, 255, 255);
	PutPixel(1 + x, 33 + y, 255, 255, 255);
	PutPixel(2 + x, 33 + y, 255, 255, 255);
	PutPixel(3 + x, 33 + y, 255, 255, 255);
	PutPixel(4 + x, 33 + y, 255, 255, 255);
	PutPixel(5 + x, 33 + y, 255, 255, 255);
	PutPixel(6 + x, 33 + y, 254, 254, 254);
	PutPixel(9 + x, 33 + y, 254, 254, 254);
	PutPixel(10 + x, 33 + y, 255, 255, 255);
	PutPixel(11 + x, 33 + y, 255, 255, 255);
	PutPixel(12 + x, 33 + y, 255, 255, 255);
	PutPixel(13 + x, 33 + y, 255, 255, 255);
	PutPixel(14 + x, 33 + y, 255, 255, 255);
	PutPixel(15 + x, 33 + y, 255, 255, 255);
	PutPixel(16 + x, 33 + y, 254, 254, 254);
	PutPixel(17 + x, 33 + y, 255, 255, 255);
	PutPixel(18 + x, 33 + y, 255, 255, 255);
	PutPixel(23 + x, 33 + y, 254, 254, 254);
	PutPixel(24 + x, 33 + y, 255, 255, 255);
	PutPixel(25 + x, 33 + y, 255, 255, 255);
	PutPixel(30 + x, 33 + y, 254, 254, 254);
	PutPixel(31 + x, 33 + y, 255, 255, 255);
	PutPixel(32 + x, 33 + y, 255, 255, 255);
	PutPixel(33 + x, 33 + y, 255, 255, 255);
	PutPixel(34 + x, 33 + y, 255, 255, 255);
	PutPixel(35 + x, 33 + y, 255, 255, 255);
	PutPixel(36 + x, 33 + y, 255, 255, 255);
	PutPixel(37 + x, 33 + y, 255, 255, 255);
	PutPixel(40 + x, 33 + y, 255, 255, 255);
	PutPixel(41 + x, 33 + y, 255, 255, 255);
	PutPixel(42 + x, 33 + y, 254, 254, 254);
	PutPixel(44 + x, 33 + y, 255, 255, 255);
	PutPixel(45 + x, 33 + y, 254, 254, 254);
	PutPixel(46 + x, 33 + y, 255, 255, 255);
	PutPixel(47 + x, 33 + y, 255, 255, 255);
	PutPixel(0 + x, 34 + y, 255, 255, 255);
	PutPixel(1 + x, 34 + y, 255, 255, 255);
	PutPixel(2 + x, 34 + y, 255, 255, 255);
	PutPixel(3 + x, 34 + y, 255, 255, 255);
	PutPixel(4 + x, 34 + y, 255, 255, 255);
	PutPixel(5 + x, 34 + y, 255, 255, 255);
	PutPixel(6 + x, 34 + y, 254, 254, 254);
	PutPixel(9 + x, 34 + y, 254, 254, 254);
	PutPixel(10 + x, 34 + y, 255, 255, 255);
	PutPixel(11 + x, 34 + y, 255, 255, 255);
	PutPixel(13 + x, 34 + y, 254, 254, 254);
	PutPixel(14 + x, 34 + y, 255, 255, 255);
	PutPixel(15 + x, 34 + y, 254, 254, 254);
	PutPixel(16 + x, 34 + y, 254, 254, 254);
	PutPixel(17 + x, 34 + y, 255, 255, 255);
	PutPixel(18 + x, 34 + y, 255, 255, 255);
	PutPixel(23 + x, 34 + y, 254, 254, 254);
	PutPixel(24 + x, 34 + y, 255, 255, 255);
	PutPixel(25 + x, 34 + y, 255, 255, 255);
	PutPixel(30 + x, 34 + y, 254, 254, 254);
	PutPixel(31 + x, 34 + y, 255, 255, 255);
	PutPixel(32 + x, 34 + y, 255, 255, 255);
	PutPixel(33 + x, 34 + y, 255, 255, 255);
	PutPixel(34 + x, 34 + y, 255, 255, 255);
	PutPixel(35 + x, 34 + y, 255, 255, 255);
	PutPixel(36 + x, 34 + y, 255, 255, 255);
	PutPixel(37 + x, 34 + y, 255, 255, 255);
	PutPixel(40 + x, 34 + y, 255, 255, 255);
	PutPixel(41 + x, 34 + y, 255, 255, 255);
	PutPixel(42 + x, 34 + y, 255, 255, 255);
	PutPixel(43 + x, 34 + y, 255, 255, 255);
	PutPixel(44 + x, 34 + y, 255, 255, 255);
	PutPixel(45 + x, 34 + y, 255, 255, 255);
	PutPixel(46 + x, 34 + y, 255, 255, 255);
	PutPixel(47 + x, 34 + y, 255, 255, 255);
	PutPixel(0 + x, 35 + y, 255, 255, 255);
	PutPixel(1 + x, 35 + y, 255, 255, 255);
	PutPixel(2 + x, 35 + y, 254, 254, 254);
	PutPixel(3 + x, 35 + y, 254, 254, 254);
	PutPixel(4 + x, 35 + y, 254, 254, 254);
	PutPixel(5 + x, 35 + y, 254, 254, 254);
	PutPixel(6 + x, 35 + y, 255, 255, 255);
	PutPixel(9 + x, 35 + y, 254, 254, 254);
	PutPixel(10 + x, 35 + y, 255, 255, 255);
	PutPixel(11 + x, 35 + y, 255, 255, 255);
	PutPixel(13 + x, 35 + y, 254, 254, 254);
	PutPixel(14 + x, 35 + y, 255, 255, 255);
	PutPixel(15 + x, 35 + y, 255, 255, 255);
	PutPixel(16 + x, 35 + y, 255, 255, 255);
	PutPixel(17 + x, 35 + y, 255, 255, 255);
	PutPixel(18 + x, 35 + y, 255, 255, 255);
	PutPixel(23 + x, 35 + y, 254, 254, 254);
	PutPixel(24 + x, 35 + y, 255, 255, 255);
	PutPixel(25 + x, 35 + y, 255, 255, 255);
	PutPixel(30 + x, 35 + y, 254, 254, 254);
	PutPixel(31 + x, 35 + y, 255, 255, 255);
	PutPixel(32 + x, 35 + y, 255, 255, 255);
	PutPixel(33 + x, 35 + y, 254, 254, 254);
	PutPixel(34 + x, 35 + y, 254, 254, 254);
	PutPixel(35 + x, 35 + y, 254, 254, 254);
	PutPixel(36 + x, 35 + y, 254, 254, 254);
	PutPixel(37 + x, 35 + y, 255, 255, 255);
	PutPixel(40 + x, 35 + y, 255, 255, 255);
	PutPixel(41 + x, 35 + y, 255, 255, 255);
	PutPixel(42 + x, 35 + y, 255, 255, 255);
	PutPixel(43 + x, 35 + y, 255, 255, 255);
	PutPixel(44 + x, 35 + y, 255, 255, 255);
	PutPixel(45 + x, 35 + y, 255, 255, 255);
	PutPixel(46 + x, 35 + y, 255, 255, 255);
	PutPixel(0 + x, 36 + y, 255, 255, 255);
	PutPixel(1 + x, 36 + y, 255, 255, 255);
	PutPixel(2 + x, 36 + y, 254, 254, 254);
	PutPixel(9 + x, 36 + y, 254, 254, 254);
	PutPixel(10 + x, 36 + y, 255, 255, 255);
	PutPixel(11 + x, 36 + y, 255, 255, 255);
	PutPixel(13 + x, 36 + y, 255, 255, 255);
	PutPixel(14 + x, 36 + y, 255, 255, 255);
	PutPixel(15 + x, 36 + y, 255, 255, 255);
	PutPixel(16 + x, 36 + y, 254, 254, 254);
	PutPixel(17 + x, 36 + y, 255, 255, 255);
	PutPixel(18 + x, 36 + y, 255, 255, 255);
	PutPixel(23 + x, 36 + y, 254, 254, 254);
	PutPixel(24 + x, 36 + y, 255, 255, 255);
	PutPixel(25 + x, 36 + y, 255, 255, 255);
	PutPixel(30 + x, 36 + y, 254, 254, 254);
	PutPixel(31 + x, 36 + y, 255, 255, 255);
	PutPixel(32 + x, 36 + y, 255, 255, 255);
	PutPixel(40 + x, 36 + y, 255, 255, 255);
	PutPixel(41 + x, 36 + y, 255, 255, 255);
	PutPixel(42 + x, 36 + y, 254, 254, 254);
	PutPixel(43 + x, 36 + y, 254, 254, 254);
	PutPixel(44 + x, 36 + y, 254, 254, 254);
	PutPixel(45 + x, 36 + y, 255, 255, 255);
	PutPixel(46 + x, 36 + y, 254, 254, 254);
	PutPixel(47 + x, 36 + y, 255, 255, 255);
	PutPixel(0 + x, 37 + y, 255, 255, 255);
	PutPixel(1 + x, 37 + y, 255, 255, 255);
	PutPixel(2 + x, 37 + y, 254, 254, 254);
	PutPixel(9 + x, 37 + y, 254, 254, 254);
	PutPixel(10 + x, 37 + y, 255, 255, 255);
	PutPixel(11 + x, 37 + y, 255, 255, 255);
	PutPixel(14 + x, 37 + y, 254, 254, 254);
	PutPixel(15 + x, 37 + y, 255, 255, 255);
	PutPixel(16 + x, 37 + y, 254, 254, 254);
	PutPixel(17 + x, 37 + y, 255, 255, 255);
	PutPixel(18 + x, 37 + y, 255, 255, 255);
	PutPixel(23 + x, 37 + y, 254, 254, 254);
	PutPixel(24 + x, 37 + y, 255, 255, 255);
	PutPixel(25 + x, 37 + y, 255, 255, 255);
	PutPixel(30 + x, 37 + y, 254, 254, 254);
	PutPixel(31 + x, 37 + y, 255, 255, 255);
	PutPixel(32 + x, 37 + y, 255, 255, 255);
	PutPixel(40 + x, 37 + y, 255, 255, 255);
	PutPixel(41 + x, 37 + y, 255, 255, 255);
	PutPixel(42 + x, 37 + y, 254, 254, 254);
	PutPixel(44 + x, 37 + y, 255, 255, 255);
	PutPixel(45 + x, 37 + y, 255, 255, 255);
	PutPixel(46 + x, 37 + y, 255, 255, 255);
	PutPixel(47 + x, 37 + y, 255, 255, 255);
	PutPixel(0 + x, 38 + y, 255, 255, 255);
	PutPixel(1 + x, 38 + y, 255, 255, 255);
	PutPixel(2 + x, 38 + y, 254, 254, 254);
	PutPixel(9 + x, 38 + y, 254, 254, 254);
	PutPixel(10 + x, 38 + y, 255, 255, 255);
	PutPixel(11 + x, 38 + y, 255, 255, 255);
	PutPixel(14 + x, 38 + y, 255, 255, 255);
	PutPixel(15 + x, 38 + y, 255, 255, 255);
	PutPixel(16 + x, 38 + y, 255, 255, 255);
	PutPixel(17 + x, 38 + y, 255, 255, 255);
	PutPixel(18 + x, 38 + y, 255, 255, 255);
	PutPixel(23 + x, 38 + y, 254, 254, 254);
	PutPixel(24 + x, 38 + y, 255, 255, 255);
	PutPixel(25 + x, 38 + y, 255, 255, 255);
	PutPixel(30 + x, 38 + y, 254, 254, 254);
	PutPixel(31 + x, 38 + y, 255, 255, 255);
	PutPixel(32 + x, 38 + y, 255, 255, 255);
	PutPixel(40 + x, 38 + y, 255, 255, 255);
	PutPixel(41 + x, 38 + y, 255, 255, 255);
	PutPixel(42 + x, 38 + y, 254, 254, 254);
	PutPixel(45 + x, 38 + y, 255, 255, 255);
	PutPixel(46 + x, 38 + y, 255, 255, 255);
	PutPixel(47 + x, 38 + y, 254, 254, 254);
	PutPixel(0 + x, 39 + y, 255, 255, 255);
	PutPixel(1 + x, 39 + y, 255, 255, 255);
	PutPixel(2 + x, 39 + y, 254, 254, 254);
	PutPixel(3 + x, 39 + y, 254, 254, 254);
	PutPixel(4 + x, 39 + y, 254, 254, 254);
	PutPixel(5 + x, 39 + y, 254, 254, 254);
	PutPixel(6 + x, 39 + y, 254, 254, 254);
	PutPixel(7 + x, 39 + y, 255, 255, 255);
	PutPixel(9 + x, 39 + y, 254, 254, 254);
	PutPixel(10 + x, 39 + y, 255, 255, 255);
	PutPixel(11 + x, 39 + y, 255, 255, 255);
	PutPixel(15 + x, 39 + y, 255, 255, 255);
	PutPixel(16 + x, 39 + y, 255, 255, 255);
	PutPixel(17 + x, 39 + y, 255, 255, 255);
	PutPixel(18 + x, 39 + y, 255, 255, 255);
	PutPixel(23 + x, 39 + y, 254, 254, 254);
	PutPixel(24 + x, 39 + y, 255, 255, 255);
	PutPixel(25 + x, 39 + y, 255, 255, 255);
	PutPixel(30 + x, 39 + y, 254, 254, 254);
	PutPixel(31 + x, 39 + y, 255, 255, 255);
	PutPixel(32 + x, 39 + y, 255, 255, 255);
	PutPixel(33 + x, 39 + y, 254, 254, 254);
	PutPixel(34 + x, 39 + y, 254, 254, 254);
	PutPixel(35 + x, 39 + y, 254, 254, 254);
	PutPixel(36 + x, 39 + y, 254, 254, 254);
	PutPixel(37 + x, 39 + y, 255, 255, 255);
	PutPixel(40 + x, 39 + y, 255, 255, 255);
	PutPixel(41 + x, 39 + y, 255, 255, 255);
	PutPixel(42 + x, 39 + y, 254, 254, 254);
	PutPixel(45 + x, 39 + y, 254, 254, 254);
	PutPixel(46 + x, 39 + y, 255, 255, 255);
	PutPixel(47 + x, 39 + y, 255, 255, 255);
	PutPixel(0 + x, 40 + y, 255, 255, 255);
	PutPixel(1 + x, 40 + y, 255, 255, 255);
	PutPixel(2 + x, 40 + y, 255, 255, 255);
	PutPixel(3 + x, 40 + y, 255, 255, 255);
	PutPixel(4 + x, 40 + y, 255, 255, 255);
	PutPixel(5 + x, 40 + y, 255, 255, 255);
	PutPixel(6 + x, 40 + y, 255, 255, 255);
	PutPixel(7 + x, 40 + y, 255, 255, 255);
	PutPixel(9 + x, 40 + y, 254, 254, 254);
	PutPixel(10 + x, 40 + y, 255, 255, 255);
	PutPixel(11 + x, 40 + y, 255, 255, 255);
	PutPixel(15 + x, 40 + y, 255, 255, 255);
	PutPixel(16 + x, 40 + y, 255, 255, 255);
	PutPixel(17 + x, 40 + y, 255, 255, 255);
	PutPixel(18 + x, 40 + y, 255, 255, 255);
	PutPixel(23 + x, 40 + y, 254, 254, 254);
	PutPixel(24 + x, 40 + y, 255, 255, 255);
	PutPixel(25 + x, 40 + y, 255, 255, 255);
	PutPixel(30 + x, 40 + y, 254, 254, 254);
	PutPixel(31 + x, 40 + y, 255, 255, 255);
	PutPixel(32 + x, 40 + y, 255, 255, 255);
	PutPixel(33 + x, 40 + y, 255, 255, 255);
	PutPixel(34 + x, 40 + y, 255, 255, 255);
	PutPixel(35 + x, 40 + y, 255, 255, 255);
	PutPixel(36 + x, 40 + y, 255, 255, 255);
	PutPixel(37 + x, 40 + y, 254, 254, 254);
	PutPixel(40 + x, 40 + y, 255, 255, 255);
	PutPixel(41 + x, 40 + y, 255, 255, 255);
	PutPixel(42 + x, 40 + y, 254, 254, 254);
	PutPixel(45 + x, 40 + y, 255, 255, 255);
	PutPixel(46 + x, 40 + y, 255, 255, 255);
	PutPixel(47 + x, 40 + y, 255, 255, 255);
	PutPixel(48 + x, 40 + y, 255, 255, 255);
	PutPixel(0 + x, 41 + y, 255, 255, 255);
	PutPixel(1 + x, 41 + y, 255, 255, 255);
	PutPixel(2 + x, 41 + y, 255, 255, 255);
	PutPixel(3 + x, 41 + y, 255, 255, 255);
	PutPixel(4 + x, 41 + y, 255, 255, 255);
	PutPixel(5 + x, 41 + y, 255, 255, 255);
	PutPixel(6 + x, 41 + y, 255, 255, 255);
	PutPixel(7 + x, 41 + y, 255, 255, 255);
	PutPixel(9 + x, 41 + y, 254, 254, 254);
	PutPixel(10 + x, 41 + y, 255, 255, 255);
	PutPixel(11 + x, 41 + y, 255, 255, 255);
	PutPixel(15 + x, 41 + y, 255, 255, 255);
	PutPixel(16 + x, 41 + y, 254, 254, 254);
	PutPixel(17 + x, 41 + y, 255, 255, 255);
	PutPixel(18 + x, 41 + y, 255, 255, 255);
	PutPixel(23 + x, 41 + y, 254, 254, 254);
	PutPixel(24 + x, 41 + y, 255, 255, 255);
	PutPixel(25 + x, 41 + y, 255, 255, 255);
	PutPixel(30 + x, 41 + y, 254, 254, 254);
	PutPixel(31 + x, 41 + y, 255, 255, 255);
	PutPixel(32 + x, 41 + y, 255, 255, 255);
	PutPixel(33 + x, 41 + y, 255, 255, 255);
	PutPixel(34 + x, 41 + y, 255, 255, 255);
	PutPixel(35 + x, 41 + y, 255, 255, 255);
	PutPixel(36 + x, 41 + y, 255, 255, 255);
	PutPixel(37 + x, 41 + y, 254, 254, 254);
	PutPixel(40 + x, 41 + y, 255, 255, 255);
	PutPixel(41 + x, 41 + y, 255, 255, 255);
	PutPixel(42 + x, 41 + y, 254, 254, 254);
	PutPixel(45 + x, 41 + y, 255, 255, 255);
	PutPixel(46 + x, 41 + y, 255, 255, 255);
	PutPixel(47 + x, 41 + y, 255, 255, 255);
	PutPixel(48 + x, 41 + y, 255, 255, 255);

}

void Graphics::DrawSpace()
{
	for (int y = 50; y < ScreenHeight; y += 100)
	{
		for (int x = 0; x < ScreenWidth; x++)
		{
			if (x % 100 == solution)
			{
				PutPixel(x, y, 255, 255, 255);
			}
		}
		if (solution == 50)
		{
			solution = 0;
		}
		else
		{
			solution = 50;
		}
	}
}


//////////////////////////////////////////////////
//           Graphics Exception
Graphics::Exception::Exception(HRESULT hr, const std::wstring& note, const wchar_t* file, unsigned int line)
	:
	ChiliException(file, line, note),
	hr(hr)
{}

std::wstring Graphics::Exception::GetFullMessage() const
{
	const std::wstring empty = L"";
	const std::wstring errorName = GetErrorName();
	const std::wstring errorDesc = GetErrorDescription();
	const std::wstring& note = GetNote();
	const std::wstring location = GetLocation();
	return    (!errorName.empty() ? std::wstring(L"Error: ") + errorName + L"\n"
		: empty)
		+ (!errorDesc.empty() ? std::wstring(L"Description: ") + errorDesc + L"\n"
			: empty)
		+ (!note.empty() ? std::wstring(L"Note: ") + note + L"\n"
			: empty)
		+ (!location.empty() ? std::wstring(L"Location: ") + location
			: empty);
}

std::wstring Graphics::Exception::GetErrorName() const
{
	return DXGetErrorString(hr);
}

std::wstring Graphics::Exception::GetErrorDescription() const
{
	std::array<wchar_t, 512> wideDescription;
	DXGetErrorDescription(hr, wideDescription.data(), wideDescription.size());
	return wideDescription.data();
}

std::wstring Graphics::Exception::GetExceptionType() const
{
	return L"Chili Graphics Exception";
}
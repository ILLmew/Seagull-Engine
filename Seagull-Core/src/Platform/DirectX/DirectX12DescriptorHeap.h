#pragma once

#include <wrl.h>
#include <d3d12.h>

using Microsoft::WRL::ComPtr;

namespace SG
{

	class DirectX12DescriptorHeap
	{
	public:
		DirectX12DescriptorHeap(ID3D12Device1* device, D3D12_DESCRIPTOR_HEAP_TYPE type, 
			UINT numDescriptors, D3D12_DESCRIPTOR_HEAP_FLAGS flag = D3D12_DESCRIPTOR_HEAP_FLAG_NONE);
		~DirectX12DescriptorHeap() = default;

		// TODO: warp ID3D12Resource with SG's own GPUResource
		void CreateRtv(ID3D12Device1* device, ID3D12Resource* resource, uint32_t index,
			const D3D12_RENDER_TARGET_VIEW_DESC* desc = nullptr);
		void CreateDsv(ID3D12Device1* device, ID3D12Resource* resource, uint32_t index,
			const D3D12_DEPTH_STENCIL_VIEW_DESC* desc);		
		void CreateSrv(ID3D12Device1* device, ID3D12Resource* resource, uint32_t index,
			const D3D12_SHADER_RESOURCE_VIEW_DESC* desc);

		D3D12_CPU_DESCRIPTOR_HANDLE GetView(uint32_t index = 0) const;
		D3D12_CPU_DESCRIPTOR_HANDLE& GetCPUStart() { return m_CPUHeapStart; }
		D3D12_GPU_DESCRIPTOR_HANDLE& GetGPUStart() { return m_GPUHeapStart; }

		ID3D12DescriptorHeap* GetNative() const { return m_DescHeap.Get(); }
		ID3D12DescriptorHeap* const* GetNativeAddress() const { return m_DescHeap.GetAddressOf(); }
	private:
		constexpr D3D12_CPU_DESCRIPTOR_HANDLE CPUOffset(uint32_t index) const;

		enum class BindingType : uint32_t
		{
			None = 0, RTV = 1, DSV = 2, UAV = 3, SRV = 4
		};
	private:
		BindingType m_BindingType;

		ComPtr<ID3D12DescriptorHeap> m_DescHeap;

		D3D12_CPU_DESCRIPTOR_HANDLE m_CPUHeapStart;
		D3D12_GPU_DESCRIPTOR_HANDLE m_GPUHeapStart;
		D3D12_DESCRIPTOR_HEAP_DESC m_HeapDesc;
		uint32_t m_DescHandleIncrementSize;
	};

}
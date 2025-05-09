#ifndef _dxrr
#define _dxrr
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>
#include <d3dx10math.h>
#include "TerrenoRR.h"
#include "Camara.h"
#include "SkyDome.h"
#include "Billboard.h"
#include "ModeloRR.h"
#include "XACT3Util.h"

#include "Text.h"
#include "GUI.h"
#include "Colisiones.h"

class DXRR {

private:
	int ancho;
	int alto;
public:
	HINSTANCE hInstance;
	HWND hWnd;

	D3D_DRIVER_TYPE driverType;
	D3D_FEATURE_LEVEL featureLevel;

	ID3D11Device* d3dDevice;
	ID3D11DeviceContext* d3dContext;
	IDXGISwapChain* swapChain;
	ID3D11RenderTargetView* backBufferTarget;

	ID3D11Texture2D* depthTexture;
	ID3D11DepthStencilView* depthStencilView;

	ID3D11DepthStencilState* depthStencilState;
	ID3D11DepthStencilState* depthStencilDisabledState;

	ID3D11BlendState* alphaBlendState, * commonBlendState;


	TerrenoRR* terreno;
	SkyDome* skydome;
	BillboardRR* billboard;
	Camara* camara;
	//ModeloRR* conejo;
	ModeloRR* Policia;
	ModeloRR* caja;
	ModeloRR* camion;
	ModeloRR* arbusto;
	ModeloRR* basura;
	ModeloRR* escuela;
	ModeloRR* casilleros;
	ModeloRR* escritorio;
	ModeloRR* hacha;
	ModeloRR* libreta;
	ModeloRR* pizarron;
	ModeloRR* puerta;
	ModeloRR* pupitre;
	ModeloRR* tablones;

	Colisiones* CAJA;

	GUI* CONEJO_BOTON_1;
	GUI* CONEJO_ESTADO_GUI_1;
	GUI* CONEJO_ESTADO_GUI_2;
	GUI* CONEJO_ALERTA_NIVEL_0;
	GUI* CONEJO_ALERTA_NIVEL_1;
	GUI* CONEJO_ALERTA_NIVEL_2;
	GUI* CONEJO_ALERTA_NIVEL_3;
	GUI* CONEJO_ALERTA_NIVEL_4;

	GUI* CONEJO_CAJA;


#pragma region ints
	int frameBillboard,
		Conejo_Nivel_Alerta = 0,
		Conejo_Estad_GUI = 1;

#pragma endregion



#pragma region floats
	float izqder,
	arriaba,
	vel,

	X_CamaraPrueba,
	Y_CamaraPrueba,
	Z_CamaraPrueba,

	PosJugadorX = 0.0f,
	PosJugadorY = 0.0f,
	PosJugadorZ = 0.0f;

#pragma endregion


#pragma region bools
	bool breakpoint,
	Colisionaste;
	bool RenderBoxUI = false;

#pragma endregion




	Text* Texto;



	



	vector2 uv1[32];
	vector2 uv2[32];
	vector2 uv3[32];
	vector2 uv4[32];

	XACTINDEX cueIndex;
	CXACT3Util m_XACT3;

	DXRR(HWND hWnd, int Ancho, int Alto)
	{
		breakpoint = false;
		frameBillboard = 0;
		ancho = Ancho;
		alto = Alto;
		driverType = D3D_DRIVER_TYPE_NULL;
		featureLevel = D3D_FEATURE_LEVEL_11_0;
		d3dDevice = 0;
		d3dContext = 0;
		swapChain = 0;
		backBufferTarget = 0;
		IniciaD3D(hWnd);
		izqder = 0;
		arriaba = 0;
		billCargaFuego();


		X_CamaraPrueba = 0.0f;
		Y_CamaraPrueba = 1.0f;
		Z_CamaraPrueba = 0.0f;
		camara = new Camara(D3DXVECTOR3(0, 80, 6), D3DXVECTOR3(0, 80, 0), D3DXVECTOR3(0, 1, 0), Ancho, Alto);


		terreno = new TerrenoRR(1000, 1000, d3dDevice, d3dContext);


		skydome = new SkyDome(32, 32, 100.0f, &d3dDevice, &d3dContext, L"skydome2.jpg");
		billboard = new BillboardRR(L"Assets/Billboards/fuego-anim.png", L"Assets/Billboards/fuego-anim-normal.png", d3dDevice, d3dContext, 5);
		//conejo = new ModeloRR(d3dDevice, d3dContext, "Assets/Conejo/CONEJO.obj", L"Assets/Conejo/CONEJO_TEXT.jpg", L"Assets/noSpecMap.jpg", 5, 0);
		
		Policia = new ModeloRR(d3dDevice, d3dContext, "Assets/Policia/POLICIA.obj", L"Assets/Policia/POLICIA_TEXT.jpg", L"Assets/Policia/POLICA_ROUGH.jpg", 8, 0);

		caja = new ModeloRR(d3dDevice, d3dContext, "Assets/Caja/CAJA.obj", L"Assets/Caja/CAJA_TEXT.jpg", L"Assets/Caja/CAJA_ROUGH.jpg", 10, 0);

		//CAJA = new Colisiones(10.0, terreno->Superficie(0, 0) + 5.0f, 0, 10, 10);
		

		camion = new ModeloRR(d3dDevice, d3dContext, "Assets/Camion/CAMION.obj", L"Assets/Camion/CAMION_TEXT.jpg", L"Assets/Camion/CAMION_ROUGH.jpg", -15, -10);
		arbusto = new ModeloRR(d3dDevice, d3dContext, "Assets/Arbusto/ARBUSTO.obj", L"Assets/Arbusto/ARBUSTO_TEXT.jpg", L"Assets/noSpecMap.jpg", -25, 5);
		basura = new ModeloRR(d3dDevice, d3dContext, "Assets/Basura/BASURA.obj", L"Assets/Basura/BASURA_TEXT.jpg", L"Assets/Basura/BASURA_ROUGH.jpg", 0, -5);

		escuela = new ModeloRR(d3dDevice, d3dContext, "Assets/Escuela/escuela.obj", L"Assets/Escuela/escuela_color.png", L"Assets/Escuela/escuela_roughness.png", -270, 20);
		casilleros = new ModeloRR(d3dDevice, d3dContext, "Assets/Casilleros/casilleros.obj", L"Assets/Casilleros/Casillero_BaseColor10.png", L"Assets/Casilleros/Casillero_Metallic100.png", -10, -45);
		escritorio = new ModeloRR(d3dDevice, d3dContext, "Assets/Escritorio/escritorio.obj", L"Assets/Escritorio/escritorio_color.png", L"Assets/noSpecMap.jpg", 10, -25);
		hacha = new ModeloRR(d3dDevice, d3dContext, "Assets/Hacha/hacha.obj", L"Assets/Hacha/axe_Albedo.png", L"Assets/Hacha/axe_Roughness.png", 8, -5);
		libreta = new ModeloRR(d3dDevice, d3dContext, "Assets/Libreta/libreta.obj", L"Assets/Libreta/tex1_baseColor.png", L"Assets/noSpecMap.jpg", -12, 5);
		pizarron = new ModeloRR(d3dDevice, d3dContext, "Assets/Pizarron/pizarron.obj", L"Assets/Pizarron/Whiteboard_BaseColor.png", L"Assets/Pizarron/Whiteboard_Roughness.png", 0, 25);

		CAJA = new Colisiones(0, terreno->Superficie(100, 20), 25, 8, 2);



		puerta = new ModeloRR(d3dDevice, d3dContext, "Assets/Puerta/PUERTA.obj", L"Assets/Puerta/PUERTA_TEXT.jpg", L"Assets/Puerta/PUERTA_ROUGH.jpg", -20,0);
		pupitre = new ModeloRR(d3dDevice, d3dContext, "Assets/Pupitre/pupitre.obj", L"Assets/Pupitre/School_desk_col.png", L"Assets/Pupitre/School_desk_rou.png", -30, -25);
		tablones = new ModeloRR(d3dDevice, d3dContext, "Assets/Tablones/tablones.obj", L"Assets/Tablones/Planks_01_t.png", L"Assets/Tablones/Planks_01_rou.png", -290, -45);

		Texto = new Text(d3dDevice, d3dContext, 3.6f, 1.2f, L"Assets/GUI/font.png", XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

#pragma region GUI
		CONEJO_ESTADO_GUI_1 = new GUI(d3dDevice, d3dContext, 0.5f, 0.5f, L"Assets/GUI/UI_CONEJO_NORMAL.png");
		CONEJO_ESTADO_GUI_2 = new GUI(d3dDevice, d3dContext, 0.5f, 0.5f, L"Assets/GUI/UI_CONEJO_ESCONDIDO.png");

		CONEJO_ALERTA_NIVEL_0 = new GUI(d3dDevice, d3dContext, 0.5f, 0.5f, L"Assets/GUI/UI_MEDIDOR_0.png");
		CONEJO_ALERTA_NIVEL_1 = new GUI(d3dDevice, d3dContext, 0.5f, 0.5f, L"Assets/GUI/UI_MEDIDOR_1.png");
		CONEJO_ALERTA_NIVEL_2 = new GUI(d3dDevice, d3dContext, 0.5f, 0.5f, L"Assets/GUI/UI_MEDIDOR_2.png");
		CONEJO_ALERTA_NIVEL_3 = new GUI(d3dDevice, d3dContext, 0.5f, 0.5f, L"Assets/GUI/UI_MEDIDOR_3.png");
		CONEJO_ALERTA_NIVEL_4 = new GUI(d3dDevice, d3dContext, 0.5f, 0.5f, L"Assets/GUI/UI_MEDIDOR_4.png");

		CONEJO_CAJA = new GUI(d3dDevice, d3dContext, 2.1f, 2.1f, L"Assets/GUI/Caja_UI.png");
		CONEJO_BOTON_1 = new GUI(d3dDevice, d3dContext, 0.1f, 0.09f, L"Assets/GUI/ui_boton.png");
#pragma endregion


	}

	~DXRR()
	{
		LiberaD3D();
		m_XACT3.Terminate();
	}

	bool IniciaD3D(HWND hWnd)
	{
		this->hInstance = hInstance;
		this->hWnd = hWnd;

		//obtiene el ancho y alto de la ventana donde se dibuja
		RECT dimensions;
		GetClientRect(hWnd, &dimensions);
		unsigned int width = dimensions.right - dimensions.left;
		unsigned int heigth = dimensions.bottom - dimensions.top;

		//Las formas en como la pc puede ejecutar el DX11, la mas rapida es D3D_DRIVER_TYPE_HARDWARE pero solo se puede usar cuando lo soporte el hardware
		//otra opcion es D3D_DRIVER_TYPE_WARP que emula el DX11 en los equipos que no lo soportan
		//la opcion menos recomendada es D3D_DRIVER_TYPE_SOFTWARE, es la mas lenta y solo es util cuando se libera una version de DX que no sea soportada por hardware
		D3D_DRIVER_TYPE driverTypes[] =
		{
			D3D_DRIVER_TYPE_HARDWARE, D3D_DRIVER_TYPE_WARP, D3D_DRIVER_TYPE_SOFTWARE
		};
		unsigned int totalDriverTypes = ARRAYSIZE(driverTypes);

		//La version de DX que utilizara, en este caso el DX11
		D3D_FEATURE_LEVEL featureLevels[] =
		{
			D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_10_0
		};
		unsigned int totalFeaturesLevels = ARRAYSIZE(featureLevels);

		DXGI_SWAP_CHAIN_DESC swapChainDesc;
		ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
		swapChainDesc.BufferCount = 1;
		swapChainDesc.BufferDesc.Width = width;
		swapChainDesc.BufferDesc.Height = heigth;
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.OutputWindow = hWnd;
		swapChainDesc.Windowed = true;
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;

		HRESULT result;
		unsigned int driver = 0, creationFlags = 0;
		for (driver = 0; driver < totalDriverTypes; driver++)
		{
			result = D3D11CreateDeviceAndSwapChain(0, driverTypes[driver], 0,
				creationFlags, featureLevels, totalFeaturesLevels,
				D3D11_SDK_VERSION, &swapChainDesc, &swapChain,
				&d3dDevice, &featureLevel, &d3dContext);

			if (SUCCEEDED(result))
			{
				driverType = driverTypes[driver];
				break;
			}
		}

		if (FAILED(result))
		{

			//Error al crear el Direct3D device
			return false;
		}

		ID3D11Texture2D* backBufferTexture;
		result = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferTexture);
		if (FAILED(result))
		{
			//"Error al crear el swapChainBuffer
			return false;
		}

		result = d3dDevice->CreateRenderTargetView(backBufferTexture, 0, &backBufferTarget);
		if (backBufferTexture)
			backBufferTexture->Release();

		if (FAILED(result))
		{
			//Error al crear el renderTargetView
			return false;
		}


		D3D11_VIEWPORT viewport;
		viewport.Width = (FLOAT)width;
		viewport.Height = (FLOAT)heigth;
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;
		viewport.TopLeftX = 0.0f;
		viewport.TopLeftY = 0.0f;

		d3dContext->RSSetViewports(1, &viewport);

		D3D11_TEXTURE2D_DESC depthTexDesc;
		ZeroMemory(&depthTexDesc, sizeof(depthTexDesc));
		depthTexDesc.Width = width;
		depthTexDesc.Height = heigth;
		depthTexDesc.MipLevels = 1;
		depthTexDesc.ArraySize = 1;
		depthTexDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthTexDesc.SampleDesc.Count = 1;
		depthTexDesc.SampleDesc.Quality = 0;
		depthTexDesc.Usage = D3D11_USAGE_DEFAULT;
		depthTexDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depthTexDesc.CPUAccessFlags = 0;
		depthTexDesc.MiscFlags = 0;

		result = d3dDevice->CreateTexture2D(&depthTexDesc, NULL, &depthTexture);
		if (FAILED(result))
		{
			MessageBox(0, L"Error", L"Error al crear la DepthTexture", MB_OK);
			return false;
		}

		D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
		ZeroMemory(&descDSV, sizeof(descDSV));
		descDSV.Format = depthTexDesc.Format;
		descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		descDSV.Texture2D.MipSlice = 0;

		result = d3dDevice->CreateDepthStencilView(depthTexture, &descDSV, &depthStencilView);
		if (FAILED(result))
		{
			MessageBox(0, L"Error", L"Error al crear el depth stencil target view", MB_OK);
			return false;
		}

		d3dContext->OMSetRenderTargets(1, &backBufferTarget, depthStencilView);

		return true;

	}

	void LiberaD3D(void)
	{
		if (depthTexture)
			depthTexture->Release();
		if (depthStencilView)
			depthStencilView->Release();
		if (backBufferTarget)
			backBufferTarget->Release();
		if (swapChain)
			swapChain->Release();
		if (d3dContext)
			d3dContext->Release();
		if (d3dDevice)
			d3dDevice->Release();

		depthTexture = 0;
		depthStencilView = 0;
		d3dDevice = 0;
		d3dContext = 0;
		swapChain = 0;
		backBufferTarget = 0;
	}

	void Render(void)
	{
		Colisionaste = false;
		
		
#pragma region aaaaaa
		float sphere[3] = { 0,0,0 };
		float prevPos[3] = { camara->posCam.x, camara->posCam.z, camara->posCam.z };
		static float angle = 0.0f;
		angle += 0.005;
		if (angle >= 360) angle = 0.0f;
		bool collide = false;
		if (d3dContext == 0)
			return;

		float clearColor[4] = { 0, 0, 0, 1.0f };
		d3dContext->ClearRenderTargetView(backBufferTarget, clearColor);
		d3dContext->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
		camara->posCam.y = terreno->Superficie(camara->posCam.x, camara->posCam.z) + 6;
		camara->UpdateCam(vel, arriaba, izqder);
		skydome->Update(camara->vista, camara->proyeccion);

		float camPosXZ[2] = { camara->posCam.x, camara->posCam.z };

		TurnOffDepth();
		skydome->Render(camara->posCam);
		TurnOnDepth();
		terreno->Draw(camara->vista, camara->proyeccion);

		PosJugadorX = camara->posCam.x;
		PosJugadorZ = camara->posCam.z;


#pragma endregion



		



		
		





#pragma region MODELOS
		//conejo->Draw(camara->vista, camara->proyeccion, terreno->Superficie(50, 20), camara->posCam, 10.0f, 0, 'A', 1);

		Policia->Draw(camara->vista, camara->proyeccion, terreno->Superficie(50, 20), camara->posCam, 10.0f, 0, 'A', 1);

		caja->Draw(camara->vista, camara->proyeccion, terreno->Superficie(50, 20), camara->posCam, 5.0f, 0, 'A', 1);
		camion->Draw(camara->vista, camara->proyeccion, terreno->Superficie(50, 20), camara->posCam, 5.0f, 0, 'A', 1);
		arbusto->Draw(camara->vista, camara->proyeccion, terreno->Superficie(50, 20), camara->posCam, 10.0f, 0, 'A', 1);
		basura->Draw(camara->vista, camara->proyeccion, terreno->Superficie(-50, -20), camara->posCam, 5.0f, 0, 'A', 1);
		escuela->Draw(camara->vista, camara->proyeccion, terreno->Superficie(100, 20), camara->posCam, 10.0f, 0, 'A', 4);
		casilleros->Draw(camara->vista, camara->proyeccion, terreno->Superficie(100, 20), camara->posCam, 5.0f, 0, 'A', 3);
		escritorio->Draw(camara->vista, camara->proyeccion, terreno->Superficie(50, 20), camara->posCam, 5.0f, 0, 'A', 5);
		hacha->Draw(camara->vista, camara->proyeccion, terreno->Superficie(100, 20), camara->posCam, 10.0f, 0, 'A', 10);
		libreta->Draw(camara->vista, camara->proyeccion, terreno->Superficie(100, -20), camara->posCam, 5.0f, 0, 'A', 10);
		pizarron->Draw(camara->vista, camara->proyeccion, terreno->Superficie(100, 20), camara->posCam, 10.0f, 0, 'A', 3);

		if (CAJA->hitbox(PosJugadorX, PosJugadorZ) == true)
		{
			//camara->posCam.x = camara->XAnte;
			//camara->posCam.z = camara->ZAnte;

			Colisionaste = true;
		}



		puerta->Draw(camara->vista, camara->proyeccion, terreno->Superficie(100, 20), camara->posCam, 5.0f, 0, 'A', 1);
		pupitre->Draw(camara->vista, camara->proyeccion, terreno->Superficie(50, 20), camara->posCam, 5.0f, 0, 'A', 4);
		tablones->Draw(camara->vista, camara->proyeccion, terreno->Superficie(5, 15), camara->posCam, 10.0f, 0, 'A', 8);

#pragma endregion


#pragma region COLISIONES

		


#pragma endregion




		




		TurnOnAlphaBlending();
#pragma region GUI


		stringstream posX;
		stringstream posY;
		stringstream posZ;
		stringstream ESTADOCOLITEST;
		stringstream Conejo_Estado;

		posX << camara->posCam.x;
		posZ << camara->posCam.z;
		posY << camara->posCam.y;
		Conejo_Estado << Conejo_Estad_GUI;

		//Colisionaste = true;

		switch (Colisionaste)
		{
		case true: {
			ESTADOCOLITEST << true;
			break;
		}
		case false: {
			ESTADOCOLITEST << false;
			break;
		}
		default:
			break;
		}
		Texto->DrawText(0.3f, 0.4f, "Estado:  " + Conejo_Estado.str(), 0.01f);
		Texto->DrawText(0.3f, 0.3f, "Coli:  " + ESTADOCOLITEST.str(), 0.01f);
		Texto->DrawText(0.3f, 0.2f, "PosX: " + posX.str(), 0.01f);
		Texto->DrawText(0.3f, 0.1f, "PosZ: " + posZ.str(), 0.01f);
		Texto->DrawText(0.3f, 0.0f, "PosY: " + posY.str(), 0.01f);
		

		CONEJO_BOTON_1->Draw(-0.7f, -0.19f);
		

		switch (Conejo_Nivel_Alerta)
		{
		case 0: {
			CONEJO_ALERTA_NIVEL_0->Draw(-0.77f, 0.0f);
			break;
		}
		case 1: {
			CONEJO_ALERTA_NIVEL_1->Draw(-0.77f, 0.0f);
			break;
		}
		case 2: {
			CONEJO_ALERTA_NIVEL_2->Draw(-0.77f, 0.0f);
			break;
		}
		case 3: {
			CONEJO_ALERTA_NIVEL_3->Draw(-0.77f, 0.0f);
			break;
		}
		case 4: {
			CONEJO_ALERTA_NIVEL_4->Draw(-0.77f, 0.0f);
			break;
		}
		default:
			CONEJO_ALERTA_NIVEL_4->Draw(-0.77f, 0.0f);
			break;
		}
		
		switch (Conejo_Estad_GUI)
		{
		case 1: {
			CONEJO_ESTADO_GUI_1->Draw(-0.77f, 0.0f);
			RenderBoxUI = false;
			break;
		}
		case 2: {
			CONEJO_ESTADO_GUI_2->Draw(-0.77f, 0.0f);
			RenderBoxUI = true;
			break;
		}
		default:
			CONEJO_ESTADO_GUI_1->Draw(-0.77f, 0.0f);
			break;
		}
		
		
		
	




#pragma endregion

#pragma region BILLBOARD

		billboard->Draw(camara->vista, camara->proyeccion, camara->posCam,
			-11, -78, 4, 5, uv1, uv2, uv3, uv4, frameBillboard);

#pragma endregion




		TurnOffAlphaBlending();

		if (RenderBoxUI == true)
		{
			CONEJO_CAJA->Draw(-0.2f, 0.0f);
		}
		


		swapChain->Present( 1, 0 );
	}

	bool isPointInsideSphere(float* point, float* sphere) {
		bool collition = false;

		float distance = sqrt((point[0] - sphere[0]) * (point[0] - sphere[0]) +
			(point[1] - sphere[1]) * (point[1] - sphere[1]));

		if (distance < sphere[2])
			collition = true;
		return collition;
	}

	//Activa el alpha blend para dibujar con transparencias
	void TurnOnAlphaBlending()
	{
		float blendFactor[4];
		blendFactor[0] = 0.0f;
		blendFactor[1] = 0.0f;
		blendFactor[2] = 0.0f;
		blendFactor[3] = 0.0f;
		HRESULT result;

		D3D11_BLEND_DESC descABSD;
		ZeroMemory(&descABSD, sizeof(D3D11_BLEND_DESC));
		descABSD.RenderTarget[0].BlendEnable = TRUE;
		descABSD.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		descABSD.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		descABSD.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		descABSD.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		descABSD.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		descABSD.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		descABSD.RenderTarget[0].RenderTargetWriteMask = 0x0f;

		result = d3dDevice->CreateBlendState(&descABSD, &alphaBlendState);
		if(FAILED(result))
		{
			MessageBox(0, L"Error", L"Error al crear el blend state", MB_OK);
			return;
		}

		d3dContext->OMSetBlendState(alphaBlendState, blendFactor, 0xffffffff);
	}

	//Regresa al blend normal(solido)
	void TurnOffAlphaBlending()
	{
		D3D11_BLEND_DESC descCBSD;
		ZeroMemory(&descCBSD, sizeof(D3D11_BLEND_DESC));
		descCBSD.RenderTarget[0].BlendEnable = FALSE;
		descCBSD.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		descCBSD.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		descCBSD.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		descCBSD.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		descCBSD.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		descCBSD.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		descCBSD.RenderTarget[0].RenderTargetWriteMask = 0x0f;
		HRESULT result;

		result = d3dDevice->CreateBlendState(&descCBSD, &commonBlendState);
		if(FAILED(result))
		{
			MessageBox(0, L"Error", L"Error al crear el blend state", MB_OK);
			return;
		}

		d3dContext->OMSetBlendState(commonBlendState, NULL, 0xffffffff);
	}

	void TurnOnDepth()
	{
		D3D11_DEPTH_STENCIL_DESC descDSD;
		ZeroMemory(&descDSD, sizeof(descDSD));
		descDSD.DepthEnable = true;
		descDSD.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		descDSD.DepthFunc = D3D11_COMPARISON_LESS;
		descDSD.StencilEnable=true;
		descDSD.StencilReadMask = 0xFF;
		descDSD.StencilWriteMask = 0xFF;
		descDSD.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		descDSD.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
		descDSD.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		descDSD.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
		descDSD.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		descDSD.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
		descDSD.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		descDSD.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		d3dDevice->CreateDepthStencilState(&descDSD, &depthStencilState);
		
		d3dContext->OMSetDepthStencilState(depthStencilState, 1);
	}

	void TurnOffDepth()
	{
		D3D11_DEPTH_STENCIL_DESC descDDSD;
		ZeroMemory(&descDDSD, sizeof(descDDSD));
		descDDSD.DepthEnable = false;
		descDDSD.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		descDDSD.DepthFunc = D3D11_COMPARISON_LESS;
		descDDSD.StencilEnable=true;
		descDDSD.StencilReadMask = 0xFF;
		descDDSD.StencilWriteMask = 0xFF;
		descDDSD.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		descDDSD.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
		descDDSD.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		descDDSD.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
		descDDSD.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		descDDSD.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
		descDDSD.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		descDDSD.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		d3dDevice->CreateDepthStencilState(&descDDSD, &depthStencilDisabledState);
		d3dContext->OMSetDepthStencilState(depthStencilDisabledState, 1);
	}

	void billCargaFuego()
	{
		uv1[0].u = .125;
		uv2[0].u = .125;
		uv3[0].u = 0;
		uv4[0].u = 0;

		uv1[0].v = .25;
		uv2[0].v = 0;
		uv3[0].v = 0;
		uv4[0].v = .25;


		for (int j = 0; j < 8; j++) {
			uv1[j].u = uv1[0].u + (j * .125);
			uv2[j].u = uv2[0].u + (j * .125);
			uv3[j].u = uv3[0].u + (j * .125);
			uv4[j].u = uv4[0].u + (j * .125);

			uv1[j].v = .25;
			uv2[j].v = 0;
			uv3[j].v = 0;
			uv4[j].v = .25;
		}
		for (int j = 0; j < 8; j++) {
			uv1[j + 8].u = uv1[0].u + (j * .125);
			uv2[j + 8].u = uv2[0].u + (j * .125);
			uv3[j + 8].u = uv3[0].u + (j * .125);
			uv4[j + 8].u = uv4[0].u + (j * .125);

			uv1[j + 8].v = .5;
			uv2[j + 8].v = .25;
			uv3[j + 8].v = .25;
			uv4[j + 8].v = .5;
		}

		for (int j = 0; j < 8; j++) {
			uv1[j + 16].u = uv1[0].u + (j * .125);
			uv2[j + 16].u = uv2[0].u + (j * .125);
			uv3[j + 16].u = uv3[0].u + (j * .125);
			uv4[j + 16].u = uv4[0].u + (j * .125);

			uv1[j + 16].v = .75;
			uv2[j + 16].v = .5;
			uv3[j + 16].v = .5;
			uv4[j + 16].v = .75;
		}

		for (int j = 0; j < 8; j++) {
			uv1[j + 24].u = uv1[0].u + (j * .125);
			uv2[j + 24].u = uv2[0].u + (j * .125);
			uv3[j + 24].u = uv3[0].u + (j * .125);
			uv4[j + 24].u = uv4[0].u + (j * .125);

			uv1[j + 24].v = 1;
			uv2[j + 24].v = .75;
			uv3[j + 24].v = .75;
			uv4[j + 24].v = 1;
		}
	}

};
#endif
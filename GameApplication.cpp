#include"GameApplication.h"

#include "Resources\ResourcesMgr.h"
#include "Utility\DirectUtility\DCamera.h"
#include "Utility\DirectUtility\DLightMgr.h"
#include "Utility\DirectUtility\DLight.h"
#include "Utility\DirectUtility\DInput.h"
#include "ID\XMLID.h"
#include "ID\PSID.h"
#include "ID\VSID.h"
#include "Utility\Frustum.h"
#include "Utility\DirectUtility\DTerrain.h"

GameApplication::GameApplication(HINSTANCE hInstance) : Application(hInstance){
	KLog::Instance()->SetTarget(K_LOG_TARGET_WINDOW);
	testframe = 0.0f;
	asdf = false;
}
GameApplication::~GameApplication(){

}
void GameApplication::initialize(){
	m_IResourcesMgr = new ResourcesMgr(m_pDev, m_hWnd);
	m_ICameraPtr = new DCamera(m_pDev);
	m_ILightMgrPtr = new DLightMgr(m_pDev);
	m_IFrustumPtr = new Frustum();
	m_ITerrainPtr = new DTerrain(m_pDev);
	m_IInput = new DInput(m_hInstance, m_hWnd);
	
	m_ICameraPtr->SetView(&Vector3(0.0f, 100.0f, -200.0f), &Vector3(0.0f, 0.0f, 0.0f), &Vector3(0.0f, 1.0f, 0.0f));

	m_ICameraPtr->SetPerspective(3.141592654f / 4.0f, 1.0f, 1.0f, 1000.0f);

	m_ILightMgrPtr->AddLight(Color3(0.0f, 0.0f, 0.0f), Color3(0.7f, 0.7f, 0.7f), Color3(0.1f, 0.1f, 0.1f), Vector3(500, 500, -500));
	
	m_IResourcesMgr->Regist(XMLID::Test, "guard.xml");

	m_IResourcesMgr->Regist(PS_ID::Test, "testps.fx");
	m_IResourcesMgr->Regist(VS_ID::Test, "testvs.fx");
	//m_IResourcesMgr->Regist(VS_ID::Test, "testshader.fx");
	m_IResourcesMgr->Regist(PS_ID::TerrainPS, "testTerrainps.fx");
	m_IResourcesMgr->Regist(VS_ID::TerrainVS, "testTerrainvs.fx");
	
	m_IFrustumPtr->Make(m_ICameraPtr->GetViewMatrixFPtr(), m_ICameraPtr->GetProjectionFPtr());


	std::string tex[1] = { "tile2.tga" };
	m_ITerrainPtr->Create(Vector3(1.0f, 0.1f, 1.0f), 0.1f, "map129.bmp", tex);
	m_ITerrainPtr->SetFrustum(m_IFrustumPtr);

	m_IResourcesMgr->Load();

	m_pVSMgr = m_IResourcesMgr->GetShaderMgr().GetVSMgr(VS_ID::Test);
	m_pPSMgr = m_IResourcesMgr->GetShaderMgr().GetPSMgr(PS_ID::Test);

	m_pTeVSMgr = m_IResourcesMgr->GetShaderMgr().GetVSMgr(VS_ID::TerrainVS);
	m_pTePSMgr = m_IResourcesMgr->GetShaderMgr().GetPSMgr(PS_ID::TerrainPS);
	

}
void GameApplication::update(float frameTimer){
	m_IInput->Update();
	if (m_IInput->GetKeyDown(DKEY_W))
	{
		m_ICameraPtr->MoveLocalZ(1.0f);
	}
	if (m_IInput->GetKeyDown(DKEY_S))
	{
		m_ICameraPtr->MoveLocalZ(-1.0f);
	}
	if (m_IInput->GetKeyDown(DKEY_A))
	{
		m_ICameraPtr->MoveLocalX(-1.0f);
	}
	if (m_IInput->GetKeyDown(DKEY_D))
	{
		m_ICameraPtr->MoveLocalX(1.0f);
	}

	m_IFrustumPtr->Make(m_ICameraPtr->GetViewMatrixFPtr(), m_ICameraPtr->GetProjectionFPtr());

	testframe += 1.0f;
	m_IResourcesMgr->GetXMLMgr().GetParsedData(XMLID::Test)->Animate(
		m_IResourcesMgr->GetXMLMgr().GetParsedData(XMLID::Test)->GetTracks(), testframe);
}
void GameApplication::draw(){
	//if (asdf)
	//{
		m_pVSMgr->SetMatrix("matView", m_ICameraPtr->GetViewMatrixFPtr());
		m_pVSMgr->SetVector3("cameraPosition", m_ICameraPtr->GetEyeFPtr());

		m_pVSMgr->SetMatrix("matProj", m_ICameraPtr->GetProjectionFPtr());
		m_pVSMgr->SetVector4("lightPosition", m_ILightMgrPtr->GetLightPtr(0)->GetPositionFPtr());

		m_pPSMgr->SetVector3("lightSpecular", m_ILightMgrPtr->GetLightPtr(0)->GetSpecularFPtr());
		m_pPSMgr->SetVector3("lightDiffuse", m_ILightMgrPtr->GetLightPtr(0)->GetDiffuseFPtr());
		m_pPSMgr->SetVector3("lightAmbient", m_ILightMgrPtr->GetLightPtr(0)->GetAmbientFPtr());

		m_IResourcesMgr->GetXMLMgr().GetParsedData(XMLID::Test)->Draw(m_pVSMgr, m_pPSMgr);
	//}
	//else
	//{
		m_pTeVSMgr->SetMatrix("matView", m_ICameraPtr->GetViewMatrixFPtr());
		m_pTeVSMgr->SetVector3("cameraPosition", m_ICameraPtr->GetEyeFPtr());

		m_pTeVSMgr->SetMatrix("matProj", m_ICameraPtr->GetProjectionFPtr());
		m_pTeVSMgr->SetVector4("lightPosition", m_ILightMgrPtr->GetLightPtr(0)->GetPositionFPtr());

		m_pTePSMgr->SetVector3("lightSpecular", m_ILightMgrPtr->GetLightPtr(0)->GetSpecularFPtr());
		m_pTePSMgr->SetVector3("lightDiffuse", m_ILightMgrPtr->GetLightPtr(0)->GetDiffuseFPtr());
		m_pTePSMgr->SetVector3("lightAmbient", m_ILightMgrPtr->GetLightPtr(0)->GetAmbientFPtr());

		m_ITerrainPtr->Draw(m_pTeVSMgr, m_pTePSMgr);
	//}
}
void GameApplication::finish(){
	KLog::DestroyInstance();
}
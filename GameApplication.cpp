#include"GameApplication.h"

#include "Utility\Camera.h"
#include "Utility\LightMgr.h"
#include "Utility\Light.h"
#include "Resources\ResourcesMgr.h"
#include "Utility\DirectUtility\DInput.h"
#include "ID\XMLID.h"
#include "ID\PSID.h"
#include "ID\VSID.h"
#include "Utility\Frustum.h"
#include "Utility\DirectUtility\DTerrain.h"
#include "Utility\KLog.h"

GameApplication::GameApplication(HINSTANCE hInstance) : Application(hInstance){
	KLog::Instance()->SetTarget(K_LOG_TARGET_WINDOW);
	testframe = 0.0f;
}
GameApplication::~GameApplication(){

}
void GameApplication::initialize(){
	m_IResourcesMgr = new ResourcesMgr(m_pDev, m_hWnd);
	m_ICameraPtr = new Camera();
	m_ILightMgrPtr = new LightMgr();
	m_IFrustumPtr = new Frustum();
	m_ITerrainPtr = new DTerrain(m_pDev);
	m_IInput = new DInput(m_hInstance, m_hWnd);
	
	m_ICameraPtr->SetView(Vector3(0.0f, 100.0f, -200.0f), Vector3(0.0f, 50.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f));

	m_ICameraPtr->SetPerspective(3.141592654f / 4.0f, 1.0f, 1.0f, 1000.0f);

	m_ILightMgrPtr->AddLight(0, Color32(0.0f, 0.0f, 0.0f), Color32(0.7f, 0.7f, 0.7f), Color32(0.1f, 0.1f, 0.1f), Vector3(500, 500, -500));
	
	KLog::Instance()->Log("Read Resources");

	m_IResourcesMgr->Regist(XMLID::Test, "./guard.xml");

	m_IResourcesMgr->Regist(PS_ID::Test, "./testps.fx");
	m_IResourcesMgr->Regist(VS_ID::Test, "./testvs.fx");
	m_IResourcesMgr->Regist(PS_ID::TerrainPS, "./testTerrainps.fx");
	m_IResourcesMgr->Regist(VS_ID::TerrainVS, "./testTerrainvs.fx");

	m_IResourcesMgr->Load();
	
	KLog::Instance()->Log("Make Frustum");
	m_IFrustumPtr->Make(m_ICameraPtr->GetViewMatrix(), m_ICameraPtr->GetProjection());

	KLog::Instance()->Log("Create Terrain");
	std::string tex[1] = { "./tile2.tga" };
	m_ITerrainPtr->Create(Vector3(1.0f, 0.1f, 1.0f), 0.1f, "./map129.bmp", tex);
	m_ITerrainPtr->SetFrustum(m_IFrustumPtr);


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
	if(m_IInput->GetKeyDown(DKEY_ENTER))
		testframe = 0.0f;

	m_IFrustumPtr->Make(m_ICameraPtr->GetViewMatrix(), m_ICameraPtr->GetProjection());

	testframe += 1.0f;
	m_IResourcesMgr->GetXMLMgr().GetParsedData(XMLID::Test)->Animate(
		m_IResourcesMgr->GetXMLMgr().GetParsedData(XMLID::Test)->GetTracks(), testframe);
}
void GameApplication::draw(){
	m_pVSMgr->SetMatrix("matView", m_ICameraPtr->GetViewMatrix());
	m_pVSMgr->SetVector3("cameraPosition", m_ICameraPtr->GetEye());

	m_pVSMgr->SetMatrix("matProj", m_ICameraPtr->GetProjection());
	m_pVSMgr->SetVector3("lightPosition", m_ILightMgrPtr->GetLight(0).GetPosition());
	m_pPSMgr->SetColor32("lightSpecular", m_ILightMgrPtr->GetLight(0).GetSpecular());
	m_pPSMgr->SetColor32("lightDiffuse", m_ILightMgrPtr->GetLight(0).GetDiffuse());
	m_pPSMgr->SetColor32("lightAmbient", m_ILightMgrPtr->GetLight(0).GetAmbient());

	m_IResourcesMgr->GetXMLMgr().GetParsedData(XMLID::Test)->Draw(m_pVSMgr, m_pPSMgr);

	m_pTeVSMgr->SetMatrix("matView", m_ICameraPtr->GetViewMatrix());
	m_pTeVSMgr->SetVector3("cameraPosition", m_ICameraPtr->GetEye());

	m_pTeVSMgr->SetMatrix("matProj", m_ICameraPtr->GetProjection());
	m_pTeVSMgr->SetVector3("lightPosition", m_ILightMgrPtr->GetLight(0).GetPosition());

	m_pTePSMgr->SetColor32("lightSpecular", m_ILightMgrPtr->GetLight(0).GetSpecular());
	m_pTePSMgr->SetColor32("lightDiffuse", m_ILightMgrPtr->GetLight(0).GetDiffuse());
	m_pTePSMgr->SetColor32("lightAmbient", m_ILightMgrPtr->GetLight(0).GetAmbient());

	m_ITerrainPtr->Draw(m_pTeVSMgr, m_pTePSMgr);
}
void GameApplication::finish(){
	KLog::DestroyInstance();
}
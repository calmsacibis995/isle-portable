#include "main.h"

#include "mxticklemanager.h"
#include "mxomnicreateparam.h"
#include "legomain.h"
#include "timeaverage.h"

#define TICKLE_INTERVAL		10		// call TickleManager every 10 msecs.
#define DEFAULT_WIDTH 640
#define DEFAULT_HEIGHT 480

#define VIDEO_HEADROOM 0.25			// 25 percent

MainApp* g_main;

MainApp::MainApp()
{
    ::SetOmniUserMessage(LegoUserMessage);
    m_running = FALSE;
    m_positioned = FALSE;
    m_tickleInterval = TICKLE_INTERVAL;
	m_pRealtimeViewWeightsDlg = NULL;
	m_pRealismDlg = NULL;
    m_pNavigationDlg = NULL;
    m_timeAverage = NULL;
    m_gameState = NULL;
	m_videoOverhead = 0;
    m_videoParam = MxVideoParam(MxRect32(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT));
    m_window = new MainWindow;
    LegoOmni::CreateInstance();
    LegoOmni::GetInstance()->Create(MxOmniCreateParam("", m_window, m_videoParam, MxOmniCreateFlags()));
    ResetVideo(m_videoParam);
	m_timeAverage = new TimeAverage(TRUE);
	m_gameState = new LegoGameState();
	MeasureVideoOverhead();
	UpdateFrameTime();
}

MainApp::~MainApp()
{
    delete m_gameState;
    delete m_timeAverage;
    delete m_pNavigationDlg;
    delete m_pRealismDlg;
    delete m_pRealtimeViewWeightsDlg;
    LegoOmni::GetInstance()->Destroy();
    LegoOmni::DestroyInstance();
    delete m_videoParam.GetPalette();
    m_startList.clear();
    m_sourceList.clear();
    delete m_window;
}

void
MainApp::Tickle(bool p_yieldOK)
{
    static MxTime lastTickleTime = 0;

    if (LegoOmni::GetInstance() && LegoOmni::GetInstance()->GetTickleManager() && LegoOmni::GetInstance()->GetTimer()) {
		MxTime currentTime = LegoOmni::GetInstance()->GetTimer()->GetTime();
		if (lastTickleTime > currentTime)
			lastTickleTime = -g_main->GetTickleInterval();

        if (currentTime > lastTickleTime + g_main->GetTickleInterval())
		{
			LegoOmni::GetInstance()->GetTickleManager()->Tickle();
            lastTickleTime = currentTime;
		}
		else if (p_yieldOK)
			Sleep(0);
	}
}

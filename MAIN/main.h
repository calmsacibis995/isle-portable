#ifndef MAIN_H
#define MAIN_H

#include "mxtimer.h"
#include "mxpalette.h"
#include "mxdsaction.h"
#include "mxvideoparam.h"
#include "legogamestate.h"

#define MxNAN_TIME  -2147483648

class StartListElement {
protected:
    LPCSTR m_source;
    MxDSAction m_action;
    MxTime m_residentTime;
public:
    StartListElement(const char* p_source, const char* p_action) {
          m_source = p_source;
          m_action.SetSourceName(p_source); 
          m_action.SetObjectName(p_action);
          m_residentTime = MxNAN_TIME;
    }
    LPCSTR GetSourceName() { return m_source; }
    LPCSTR GetActionName() { return m_action.GetObjectName(); }
    MxDSAction* GetAction() { m_action.SetSourceName(m_source); return &m_action; }
};

class StartList : public std::list<std::unique_ptr<StartListElement>> {};

class SourceListElement {
protected:
    LPCSTR m_source;
    UINT m_mode;
public:
    SourceListElement(const char* p_source, UINT p_mode) { m_source = p_source; m_mode = p_mode; }
    LPCSTR& GetSource() { return m_source; }
    UINT GetMode() { return m_mode; }
};

class SourceList : public std::list<std::unique_ptr<SourceListElement>> {};

class MainApp {
protected:
    bool m_running;
    bool m_positioned;
    MxTime m_tickleInterval;
    MxVideoParam m_videoParam;
    CRVWeightsDlg* m_pRealtimeViewWeightsDlg;
	CRealismDlg* m_pRealismDlg;
	CNavDlg* m_pNavigationDlg;
    TimeAverage* m_timeAverage;
    LegoGameState* m_gameState;
    StartList m_startList;
    SourceList m_sourceList;
    MainWindow* m_window;
    int m_videoOverhead;
public:
    MainApp();
    ~MainApp();
    bool GetRunning() { return m_running; }
    void SetRunning(bool p_running) { m_running = p_running; }
    bool GetPositioned() { return m_positioned; }
    void SetPositioned(bool p_positioned) { m_positioned = p_positioned; }
    MxTime GetTickleInterval() { return m_tickleInterval; }
    void SetTickleInterval(MxTime p_tickleInterval) { m_tickleInterval = p_tickleInterval; }
    MxVideoParam& GetVideoParam() { return m_videoParam; }
    void SetVideoParam(MxVideoParam& p_videoParam) { m_videoParam = p_videoParam; }
    MainWindow* GetWindow() { return m_window; }
    void ResetVideo(MxVideoParam& p_videoParam);
	void Tickle(bool p_yieldOK);
	int GetVideoOverhead() { return m_videoOverhead; }
	void MeasureVideoOverhead();
	void UpdateFrameTime();
};

class MainWindow {
protected:
    void Open(UINT p_openMode);
    bool ChangeVideoMode(int p_width, int p_height);
public:
	MainWindow();
    ~MainWindow();
    void Resize(int p_width, int p_height, bool p_titleBar);
};

extern void LegoUserMessage(const char *p_txt, int p_type);

#endif
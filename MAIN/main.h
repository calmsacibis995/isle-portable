#ifndef MAIN_H
#define MAIN_H

#include "mxtimer.h"
#include "mxpalette.h"
#include "mxvideoparam.h"

class MxPalette;
class TimeAverage;

class MainApp {
protected:
    bool m_running;
    bool m_positioned;
    MxTime m_tickleInterval;
    MxVideoParam m_videoParam;
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
    void ResetVideo(MxVideoParam& p_videoParam);
	void Tickle(bool p_yieldOK);
	int GetVideoOverhead() { return m_videoOverhead; }
	void MeasureVideoOverhead();
	void UpdateFrameTime();
};

extern void LegoUserMessage(const char *p_txt, int p_type);

#endif
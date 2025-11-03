#ifndef TIMEAVERAGE_H
#define TIMEAVERAGE_H

#include "mxpresenter.h"

#define MAX_FRAME_TIME 1000
#define BIN_MAX 100
#define BIN_INCREMENT (MAX_FRAME_TIME/BIN_MAX)

class TimeAverage : public MxPresenter {
protected:
	MxTime	m_minTime;
	MxTime	m_maxTime;
	MxTime	m_lastTime;
	MxTime	m_sum;
	int		m_count;
	MxBool	m_resetAtNextTickle;
	int		m_timeBins[BIN_MAX];

public:
	TimeAverage(MxBool);
	TimeAverage();
	virtual ~TimeAverage();
	void Create(MxBool p_delayedStart);
	virtual MxResult Tickle();
	virtual void EndAction() {};
	virtual MxResult StartAction(MxStreamController* p_controller, MxDSAction* p_action) { return SUCCESS; }
	virtual void Destroy() {}
	virtual MxResult Create() { return SUCCESS; }


	void	ResetAtNextTickle() { m_resetAtNextTickle = TRUE; }
	MxTime	GetMin() { return m_minTime; }
	MxTime	GetMax() { return m_maxTime; }
	MxTime	GetAverage() { return m_count ? m_sum/m_count : 0; }
	void	Print();
	MxS32	Notify(MxParam& p_param);


    static const MxS8* HandlerClassName() { return "TimeAverage"; }
    virtual const MxS8* ClassName() { return HandlerClassName(); }
};

#endif

#ifndef __SIGNAL_SLOT_H__
#define __SIGNAL_SLOT_H__

class Switch
{
public:
	virtual void Clicked() = 0;
};

class Light
{
public:
	void ToggleState();
	void TurnOn();
	void TurnOff();
};

class ToggleSwitch: public Switch
{
public:
	ToggleSwitch(Light& lp) 
	{
		m_lp = lp;
	}

	virtual void Clicked() {
		m_lp.ToggleState();
	}

private:
	Light& m_lp;
};


#endif
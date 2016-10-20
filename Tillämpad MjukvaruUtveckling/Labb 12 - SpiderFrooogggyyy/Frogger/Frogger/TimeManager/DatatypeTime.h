#ifndef TIMEMANAGER_TIME_HEADER 
#define TIMEMANAGER_TIME_HEADER 

namespace CommonUtilities
{
	enum Clocks
	{
		SYSTEM_CLOCK,
		MASTER_CLOCK,
		FULL_RUN_CLOCK,
		CIRCLE_BOX_CLOCK,
		LINE_CLOCK,
		GAME_CLOCK,
		GUI_CLOCK,
		NUM_CLOCKS,
		ANY_CLOCK
	};

	class Time
	{
	public:
		Time();
		Time(const Clocks aClock,const double aTime);
		Time(const Time& aTime);
		~Time();

		Time& operator=(const Time& aTime);
		Time& operator=(const float& aFloat);
		Time& operator=(const double& aDouble);
		Time& operator=(const Clocks& aClock);
		

		//Compound operators
		Time& operator*=(const Time& aTime);
		Time& operator+=(const Time& aTime);
		Time& operator-=(const Time& aTime);
		Time& operator*=(const float& aTime);
		Time& operator*=(const double& aTime);
		Time& operator+=(const float& aTime);
		Time& operator+=(const double& aTime);
		Time& operator-=(const float& aTime);
		Time& operator-=(const double& aTime);


		// Comparison operators
		bool operator<(const Time &aTime) const;
		bool operator>(const Time &aTime) const;
		bool operator<=(const Time &aTime) const;
		bool operator>=(const Time &aTime) const;

		double GetTime() const;
		Clocks GetClock() const;

		void SetTime(const double aTime);
		void SetClock(const Clocks aClock);
	private:
		Clocks myClock;
		double myTime;
	};

	// Time to Time operators
	Time operator+(const Time& aLeftSideTime,const Time& aRightSideTime);
	Time operator-(const Time& aLeftSideTime,const Time& aRightSideTime);
	Time operator*(const Time& aLeftSideTime,const Time& aRightSideTime);		

	//time to float operators
	float	operator*(const float& aLeftSideTime,const Time& aRightSideTime);
	Time	operator*(const Time& aLeftSideTime,const float& aRightSideTime);
	float	operator+(const float& aLeftSideTime,const Time& aRightSideTime);
	double	operator+(const double& aLeftSideTime,const Time& aRightSideTime);
	Time	operator+(const Time& aLeftSideTime,const float& aRightSideTime);
	Time	operator+(const Time& aLeftSideTime,const double& aRightSideTime);
};

#endif
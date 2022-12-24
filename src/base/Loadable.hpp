#ifndef BASE_LOADABLE_HPP
#define BASE_LOADABLE_HPP

class Setup {
	public:
		virtual void setup() = 0;
};

class Looper {
	public:
		virtual void loop() = 0;
};

class Loadable : public Setup, public Looper {};

#endif

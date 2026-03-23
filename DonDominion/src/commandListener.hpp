#pragma once


namespace dominion {
	class CommandListener {
		public:
			CommandListener();
			virtual ~CommandListener();
			virtual void goLeft();
			virtual void goRight();

	};

}

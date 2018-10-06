#ifndef STORYDATA
#define STORYDATA

#include <string>

class StoryData {
	public:
		std::string message = "";
		std::string background = "";
		std::string speakername = "";
		std::string speakerimage = "";
		bool fadeAfter = false;
		StoryData();
		~StoryData();
};

#endif
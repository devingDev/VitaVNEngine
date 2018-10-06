#include <psp2/kernel/processmgr.h>
#include <sstream>
#include <vector>
#include <psp2/io/fcntl.h>
#include <vita2d.h>
#include <map>

#include "json.hpp"

#include "StoryData.hpp"
#include "VitaPad.hpp"



VitaPad vitaPad;

int storyLinesAmount = 0;
std::vector<StoryData> storyData;
std::map< std::string, vita2d_texture * > imagesMap;
vita2d_font * textFont;

int loadStory(){
	int fhStory = sceIoOpen("app0:assets/story/story.json" , SCE_O_RDONLY , 0777);
	if(fhStory < 0){
		return -1;
	}
	int fileSize = sceIoLseek ( fhStory, 0, SCE_SEEK_END );
	sceIoLseek ( fhStory, 0, SCE_SEEK_SET ); 
	std::string storyJsonString(fileSize , '\0');
	sceIoRead(fhStory , &storyJsonString[0] , fileSize );
	sceIoClose(fhStory);
	
	nlohmann::json storyJSON = nlohmann::json::parse(storyJsonString);
	
	storyData.clear();
	
	if(!storyJSON.is_null()){
		if(!storyJSON["story"].is_null()){
			storyLinesAmount = storyJSON["story"].size();
			
			for(int i = 0; i < storyLinesAmount; i++){
				if(!storyJSON["story"][i].is_null()){
					StoryData storyData;
					if(!storyJSON["story"][i]["message"].is_null()){
						storyData.message = storyJSON["story"][i]["message"].get<std::string>();
					}else{
						storyData.message = "";
					}
					if(!storyJSON["story"][i]["background"].is_null()){
						storyData.background = storyJSON["story"][i]["background"].get<std::string>();
					}else{
						storyData.background = "";
					}
					if(!storyJSON["story"][i]["speakername"].is_null()){
						storyData.speakername = storyJSON["story"][i]["speakername"].get<std::string>();
					}else{
						storyData.speakername = "";
					}
					if(!storyJSON["story"][i]["speakerimage"].is_null()){
						storyData.speakerimage = storyJSON["story"][i]["speakerimage"].get<std::string>();
					}else{
						storyData.speakerimage = "";
					}
					if(!storyJSON["story"][i]["fadeAfter"].is_null()){
						storyData.fadeAfter = storyJSON["story"][i]["fadeAfter"].get<bool>();
					}else{
						storyData.fadeAfter = "";
					}
				}
			}
			
		}
	}
	
	return 0;
}

void SetupVita2D(){
	vita2d_init();
	vita2d_set_clear_color(RGBA8(0x40, 0x40, 0x40, 0xFF));
	textFont = vita2d_load_font_file("app0:assets/font/textFont.ttf");
	
	
	
}


void LoadImages(){
	
	// how to check if already in here : 
	if ( imagesMap.find("f") == imagesMap.end() ) {
		// not found
		
	} else {
		// found
		
	}
}

int main(int argc, char *argv[]) {
	
	SetupVita2D();
	
	vita2d_start_drawing();
	vita2d_clear_screen();
	vita2d_font_draw_text(textFont, 20, 90, RGBA8(0xFF, 0xFF, 0xFF, 0xFF), 32, "Press X to load story");
	vita2d_end_drawing();
	vita2d_swap_buffers();
	
	while(!vitaPad.cross){
		vitaPad.Read();
		sceKernelDelayThread(100);
	}
	
	if(loadStory() != 0){
		return 0;
	}
	
	
	LoadImages();
	
	
	while(true){
		vitaPad.Read();
		vita2d_start_drawing();
		vita2d_clear_screen();
		vita2d_font_draw_text(textFont, 20, 90, RGBA8(0xFF, 0xFF, 0xFF, 0xFF), 32, "Loaded ! .. now wait for dev to finish the rest :)");
		vita2d_end_drawing();
		vita2d_swap_buffers();
		sceKernelDelayThread(100);
	}
	
	
	sceKernelExitProcess(0);
    return 0;
}

from dotenv import load_dotenv
import os
import unreal
import aiohttp
import asyncio
import threading


class StoryTool():
    def __init__(self):
        self.link_story_collection = os.getenv("LINK_STORY_COLLECTION")
        self.access_key = os.getenv("ACCESS_KEY")


    async def async_get_request(self, url):
        async with aiohttp.ClientSession() as session:
            async with session.get(url) as response:
                if response.status == 200:
                    data = await response.json()
                else:
                    data = {}

                return response.status, data
    

    async def get_link_story(self):
        link = f"{self.link_story_collection}?access_key={self.access_key}"
        status_code, story_object = await self.async_get_request(link)

        if len(story_object.items()) == 0:
            unreal.log_warning(f"Response status: {status_code}")
            return
        
        game_story_method_list: list = story_object["collection"]["item"][0]["item"]
        unreal.log(f"Methods in game story {len(game_story_method_list)}")

    
    def start_thread_get_link_story(self):
        thread_get_link_story = threading.Thread(
            target=asyncio.run, 
            args=(self.get_link_story(), )
        )
        thread_get_link_story.start()


    def run(self):
        self.start_thread_get_link_story()
        unreal.log("Halo")


if __name__ == "__main__":
    project_dir = unreal.SystemLibrary.get_project_directory()
    dotenv_path = os.path.join(project_dir, ".env")

    if load_dotenv(dotenv_path=dotenv_path):
        unreal.log("Success load environment variables")
        story_tool = StoryTool()
        story_tool.run()
    else:
        unreal.log_error("Couldn't load environment variables")

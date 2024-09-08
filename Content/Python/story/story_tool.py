import unreal
import aiohttp
import asyncio


class StoryTool():
    def __init__(self):
        self.link_story_collection = ""
        self.access_key = ""


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


    def run(self):
        with unreal.ScopedSlowTask(1, "Running...") as slow_task:
            slow_task.make_dialog()
            asyncio.run(self.get_link_story())


if __name__ == "__main__":
    story_tool = StoryTool()
    story_tool.run()

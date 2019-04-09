#include "PlaceBot.h"
#include "BotManager.h"

void PlaceBot::Update(float dt)
{
	ConnectionBot::Update(dt);

	World &world = mManager.GetWorld();
	TaskManager &taskManager = mManager.GetTaskManager();
	TaskManager &retryPot = mManager.GetRetryPot();

	if (mConnectionState >= ConnectionState::Joined)
	{

		for (int max = 50; max > 0 && mPlaceBucket.CanSpend(1) && taskManager.GetNumTasks(Task::PlacePixel); max--)
		{
			Task placeTask;
			while (taskManager.PopTask(Task::PlacePixel, placeTask))
			{
				if (world.GetPixel(placeTask.pos) != placeTask.color)
				{
					retryPot.PushTask(placeTask);

					if (!PlacePixel(placeTask.pos, placeTask.color))
						taskManager.PushTask(placeTask);
					break;
				}
			}
		}


		if (mRunWorldHandler)
		{
			Task chunkTask;
			for (int max = 25; max > 0 && taskManager.PopTask(Task::RequestChunk, chunkTask); max--)
			{
				if (!RequestChunk(chunkTask.pos))
					taskManager.PushTask(chunkTask);
			}
		}

		static sf::Clock errorTimeout;
		if (errorTimeout.getElapsedTime().asSeconds() > 2)
		{
			errorTimeout.restart();
		}

	}
}

void PlaceBot::MessageHandler(const std::shared_ptr<Protocol::IS2CMessage>& message)
{
	ConnectionBot::MessageHandler(message);

	if (mRunWorldHandler)
	{
		mManager.GetWorld().HandlePacket(message);
	}
}


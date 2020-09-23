#include "BubbleSort.hpp"
#include "common/useful.hpp"

static bool processEvents(RenderWindow &window)
{
	Event e;
	while (window.pollEvent(e))
		switch (e.type)
		{
			case Event::Closed:
				window.close();
				break;
			default:
				break;
		}
	return pressed(sf::Keyboard::Q);
}

void BubbleSort(RenderWindow &window, std::vector<RectangleShape> V)
{
	window.clear(Color::Black);
	for (auto& rect : V)
		window.draw(rect);
	window.display();

	bool change = true;
	int howMany = 0;
	while (change)
	{
		change = false;
		++howMany;
		for (size_t i = 0; i < V.size() - howMany; ++i)
		{
			auto& rect1 = V[i], &rect2 = V[i + 1];
			rect1.setFillColor(Color::Green);
			rect2.setFillColor(Color::Red);

			int highI = rect1.getLocalBounds().height;
			int highJ = rect2.getLocalBounds().height;
			if (highI > highJ)
			{
				Vector2f posI = rect1.getPosition(), posJ = rect2.getPosition();
				rect1.setPosition(posJ); rect2.setPosition(posI);
				rect1.setFillColor(Color::Red); rect2.setFillColor(Color::Green);
				std::swap(rect1, rect2);
				change = true;
			}

			if (processEvents(window))
				return;

			window.clear(Color::Black);
			for(size_t j = 0; j < V.size(); ++j)
				window.draw(V[j]);
			window.display();

			sleep(seconds(0.005));

			rect1.setFillColor(Color::White);
			if(i == V.size() - howMany - 1) rect2.setFillColor(Color::White);
		}
	}
}

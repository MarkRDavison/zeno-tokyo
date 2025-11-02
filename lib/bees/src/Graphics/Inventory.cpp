#include <tokyo/Bees/Graphics/Inventory.hpp>
#include <tokyo/Bees/Constants.hpp>
#include <tokyo/Bees/BeeInstance.hpp>
#include <tokyo/Core/Infrastructure/TextureManager.hpp>
#include <SFML/Graphics.hpp>

namespace bee
{

	void Inventory::draw(Player* player, sf::RenderTarget & target, sf::RenderStates states) const
	{
		if (player != nullptr)
		{
			auto& textureManager = BeeInstance::Get().TextureManager;
			auto& font = BeeInstance::Get().FontManager.getFont("arial");

			sf::RectangleShape r({ 64.0f, 64.0f });
			r.setFillColor(sf::Color::White);
			r.setOutlineColor(sf::Color::Black);
			r.setOutlineThickness(2.0f);


			const float squareSize = 64.0f + 4.0f + 4;

			states.transform.translate({ target.getSize().x / 2 - squareSize * (float)(Constants::InventorySlots) / 2.0f, target.getSize().y - 64.0f - 2.0f });

			for (int i = 0; i < Constants::InventorySlots; ++i)
			{
				r.setOutlineColor(i == player->getActiveInventorySlot() ? sf::Color::Yellow : sf::Color::Black);
				r.setOutlineThickness(i == player->getActiveInventorySlot() ? 4.0f : 2.0f);

				target.draw(r, states);

				const auto& slot = player->getInventoryAtSlot(i);
				if (!slot.texture.empty())
				{
					sf::Sprite icon(textureManager.getTexture(slot.texture));
					target.draw(icon, states);
				}
				if (slot.count > 0)
				{
					auto tstates(states);
					sf::Text text(font, std::to_string(slot.count), 20);
					text.setFillColor(sf::Color::White);
					text.setOutlineColor(sf::Color::Black);
					text.setOutlineThickness(2.0f);
					tstates.transform.translate({ 0.0f, squareSize - 24.0f - 6.0f  });
					target.draw(text, tstates);
				}

				states.transform.translate({ squareSize, 0.0f });
			}
		}
	}

}
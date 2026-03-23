#ifndef PLAYER_INVENTORY_H_
#define PLAYER_INVENTORY_H_

#include "engine/Components/Component.h"
#include "engine/Components/Font.h"

class PlayerInventory : public Component
{
	private:
		Font* m_font;
		int m_playerPoints;
		bool m_hasSuperPunch;
	public:
		PlayerInventory(GameObject*, Font* = nullptr);
		~PlayerInventory();
		void OnIterate();
		std::unique_ptr<Component> copy();
		void AddPoints(int val);
		void SetPunch();

		int GetPlayerPoints() const;
		bool HasSuperPunch() const;

		void SetFont(Font*);

};

#endif

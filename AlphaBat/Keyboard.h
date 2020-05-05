void Keyboard()
{
	if(key['W']||key[VK_UP])
		Player.Forward();
	if(key['S']||key[VK_DOWN])
		Player.Back();
	if(key['A']||key[VK_LEFT])
		Player.Left();
	if(key['D']||key[VK_RIGHT])
		Player.Right();
	if(key['P'])
	{
		Player.GOD();
	}
}
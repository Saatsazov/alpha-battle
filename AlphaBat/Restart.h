void RestartLevel()
{
	Player.SetPosition(Level.PlayerPos);
	Player.SetHAngle(Level.PlayerHAngle);
	Player.SetVAngle(Level.PlayerVAngle);
	bullets.Reset();
	Level.Mishen.Reset();
	Score = 0;
}
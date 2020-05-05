LRESULT CALLBACK WndProc (HWND hWnd, UINT message,
                          WPARAM wParam, LPARAM lParam)
{

    switch (message)
    {
	case WM_KILLFOCUS:
		ShowCursor(CursorState=TRUE);
		Menu.EnterMenu();
		return 0;
		break;
	case WM_SETFOCUS:
		ShowCursor(CursorState=FALSE);
		Menu.EnterMenu();
		return 0;
		break;
	case WM_SIZE:
	case WM_MOVE:
		WindowResize();
		return 0;
		break;
    case WM_CREATE:
        return 0;
    case WM_CLOSE:
        PostQuitMessage (0);
        return 0;
    case WM_DESTROY:
        return 0;
	case WM_LBUTTONDOWN:
		if(!Pause)
		{
			if(Sound)
				alSourcePlay (FireSrc);
			bullets.NewBull();
			TCannonUP = true;
			TCannon = true;
		}
		return 0;
		break;
	case WM_KEYUP:
		if(!Pause)
			key[wParam]=false;
		return 0;
		break;
    case WM_KEYDOWN:
		if(!Pause)
			key[wParam]=true;
        switch (wParam)
        {
		case VK_ESCAPE:
			if(Pause)
				Menu.CheckEscape();
			else
				Menu.EnterMenu();
			break;
		case VK_RETURN:
			if(Pause)
				Menu.CheckReturn();
			break;
		case VK_DOWN:
		case VK_LEFT:
			Menu.CheckDown();
			break;
		case VK_UP:
		case VK_RIGHT:
			Menu.CheckUp();
			break;
        }
        return 0;
	

    default:
        return DefWindowProc (hWnd, message, wParam, lParam);
    }
}
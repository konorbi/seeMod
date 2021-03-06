//------------------------------------------------------------------------------
// File:	f_samp.inc (version: 1.0x u1)
//
// Le�r�s:	Ez a f�jl megk�nnyebb�ti a pawn nyelv haszn�lat�t. Sok gyakran haszn�lt
//          f�ggv�nyt tartalmaz.
//
// Log:  	2009/06/29 (verzi�: 1.0)
//				- Els� verzi� megjelen�se
//
//          2009/06/29  (verzi�: 1.0x)
//              - Tov�bbi f�ggv�nyek hozz�ad�sa.
//              - Tov�bbi inf�rm�ci� egyes f�ggv�nyekr�l.
//
//          2009/06/29  (verzi�: 1.0x u1)
//              - Hibajav�t�sok elv�gezve.
//
// K�sz�t�: Epsilon & [_PGB_]Spatrik
//
// Minden jog fenntartva, Copyright
//------------------------------------------------------------------------------

/*------------------------------------------------------------------------------
native Instaset(b);
native SetTeleport(tpname[] ,id ,Float:x ,Float:y ,Float:z ,Float:a ,interior);
native ClearChat(playerid);
native GetVehicleDriver(vehid);
native ClearChatToAll();
native GET_PLAYER_NAME(playerid);
native GET_PLAYER_IP(playerid);
native KillPlayer(playerid);
native ReturnUser(estr[]);
native GivePlayerScore(playerid, score);
native GivePlayerWantedLevel(playerid, level);
native InstasetEx(b)
native Cenzura(word, text);
native OnlinePlayers();
native OffMusic(id);
native OffMusicForAll();
native PlaySoundForAll(soundid);
native SetPlayerMoney( id, mani );
native DestroyAllVehicles();
native KickEx(playerid, textcolor, reason[]);
native GivePlayerHealth(id, Float:h);
native WriteFile(file[], text[]);
native fcreate(fname[], fformat[]);
native IsTeamKill(playerid, killerid);
native IsSamePlayerTeam(playerid, killerid);
native IsNumeric(string[]);
native AntiDeamx();
native PlayerToPoint(Float:radi, playerid, Float:x, Float:y, Float:z);
native strsplit(const source[], dest[][], seprator);
native strcpy(dest[], const source[], max = 255, len = -1);
native strtok(const source[], &index);
native sscanf(string[], format[], {Float,_}:...);
native OffRPName(id);
------------------------------------------------------------------------------*/

//------------------------------------------------------------------------------
// Biztons�gi r�s
//------------------------------------------------------------------------------
#if defined functions_include
	#endinput
#endif
#define functions_include
#define Version "1.0x"

//------------------------------------------------------------------------------
// A szabv�nyos SA:MP f�ggv�nyek be�gyaz�sa
//------------------------------------------------------------------------------
#include <a_samp>

//------------------------------------------------------------------------------
// Sz�nek defini�l�sa
//------------------------------------------------------------------------------
#define COLOR_ORANGE 	(0xFF9900AA)
#define COLOR_RED 		(0xFF0000AA)
#define COLOR_WHITE 	(0xFFFFFFAA)
#define COLOR_GREEN 	(0x008000AA)
#define COLOR_PINK 		(0xC715FFAA)
#define COLOR_YELLOW 	(0xFFFF00AA)
#define COLOR_LIGHTBLUE (0x00FFFFAA)
#define COLOR_BLUE 		(0x0000FFAA)
#define COLOR_PURPLE    (0x9900FFAA)
#define COLOR_GREY 		(0xAFAFAFAA)


//------------------------------------------------------------------------------
// #define �lland�k
//------------------------------------------------------------------------------
#define dcmd(%1,%2,%3) if ((strcmp((%3)[1], #%1, true, (%2)) == 0) && ((((%3)[(%2) + 1] == 0) && (dcmd_%1(playerid, "")))||(((%3)[(%2) + 1] == 32) && (dcmd_%1(playerid, (%3)[(%2) + 2]))))) return 1
#define foreach(%1) \
		for (new %1 = 0; %1 < GetMaxPlayers(); %1++) if (IsPlayerConnected(%1))
	
//------------------------------------------------------------------------------
// N�v: Instaset
// Le�r�s: Ki vagy bekapcsolja a szerveren az instagibet. Azaz egy l�v�s = hal�l.
// Protot�pus: Instaset( 0 = ki | 1 = be )
// K�sz�t�: Epsilon
//------------------------------------------------------------------------------
stock Instaset(b)
{
	// Ha a bet�pl�lt �rt�k 1 akkor,
	if(b == 1) SendRconCommand("instagib 1");
	// Ha 0 akkor pedig
		else if(b == 0) SendRconCommand("instagib 0");
	// Ha egyiksem visszat�r�nk null�val	
			else return 0;
	// A f�ggv�ny gondn�lk�li lefut�sa ut�n eggyel t�r vissza		
	return 1;
}

//------------------------------------------------------------------------------
// N�v: InstasetEx
// Le�r�s: Ki vagy bekapcsolja a szerveren az instagibet. Azaz egy l�v�s = hal�l. 
//                          Ezenk�v�l visszat�r a megadott �rt�kkel
// Protot�pus: InstasetEx( 0 = ki | 1 = be )
// K�sz�t�: Epsilon
//------------------------------------------------------------------------------
stock InstasetEx(b)
{
	// Ha a bet�pl�lt �rt�k 1 akkor,
	if(b == 1) SendRconCommand("instagib 1");
	// Ha 0 akkor pedig
		else if(b == 0) SendRconCommand("instagib 0");
	// Ha egyiksem visszat�r�nk -1el	
			else return -1;
	// A f�ggv�ny gondn�lk�li lefut�sa ut�n a megadott �rt�kkel t�r vissza		
	return b;
}

//------------------------------------------------------------------------------
// N�v: SetTeleport
// Le�r�s: A teleportok l�trehoz�s�t k�nny�ti meg.
// K�sz�t�: Epsilon, Spatrik
//------------------------------------------------------------------------------
stock SetTeleport(tpname[] , id , Float:x , Float:y , Float:z , Float:a , interior )
{	
	// Ha a j�t�kos j�rm�ben van �s � vezeti,
	if( GetPlayerState( playerid ) == PLAYER_STATE_DRIVER )
	{
		// Akkor elteleport�ljuk a j�rm�vet az adott koordin�t�ra.
		SetVehiclePos( GetPlayerVehicleID( id ) , x, y, z );

		// Be�ll�tjuk az elfordul�si sz�g�t.
		SetVehicleZAngle( GetPlayerVehicleID( id ) , a );

		// Elehelyezz�k az adott interiorba.
		LinkVehicleToInterior( GetPlayerVehicleID( id ) , interior );
	}
	// Ha a j�tkos nem tart�zkodik j�rm�ben vagy nem vezeti azt,
	else
	{
		// Akkor elteleport�ljuk a j�t�kost az adott koordin�t�ra.
		SetPlayerPos( id , x , y , z );

		// Be�ll�tjuk az elfordul�si sz�g�t.
		SetPlayerFacingAngle( id , a );

		// A kamer�t a j�t�kos m�g� helyezz�k.
		SetCameraBehindPlayer( id );
	}

	// Elhelyezz�k a j�t�kost az adott interiorba.
	SetPlayerInterior( id , interior );

	// 128 karaktert torol� adatt�rol� l�trehoz�sa az �zenet sz�m�ra.
	new estr[ 128 ];

	// �zenet megform�z�sa.
	format( estr , 128 , "%s elteleport�lt ide: %s" , GET_PLAYER_NAME( playerid ) , tpname );

	// Elk�ldj�k mindenkinek az el�re megform�zott �zenetet.
	SendClientMessageToAll( COLOR_YELLOW , estr );

	// Visszat�r�s
	return 1;
}


//------------------------------------------------------------------------------
// N�v: ClearChat
// Le�r�s: A Chatboxot lehet vele egyszer�en t�r�lni egy j�t�kosn�l.
// K�sz�t�: Epsilon
//------------------------------------------------------------------------------
stock ClearChat(playerid)
{
	// A ciklus seg�tsg�vel 51-szer elk�ldj�k az �res �zenetet.
	for(new a = 1; a <= 51; a++) SendClientMessage(playerid, COLOR_WHITE, "\n");

	// Visszat�r�s
	return 1;
}

//------------------------------------------------------------------------------
// N�v: ClearChatToAll
// Le�r�s: A Chatboxot lehet vele egyszer�en t�r�lni, ez viszont midnenkire hat.
// K�sz�t�: Spatrik
//------------------------------------------------------------------------------
stock ClearChatToAll()
{
	// A ciklus seg�tsg�vel 51-szer elk�ldj�k az �res �zenetet mindenkinek.
	for(new i = 1; i <= 51; i++) SendClientMessageToAll(COLOR_WHITE, "\n");

	// Visszat�r�s
	return 1;
}

//------------------------------------------------------------------------------
// N�v: GET_PLAYER_NAME
// Le�r�s: A j�t�kos nev�t lehet vele egyszer�en lek�rni.
// K�sz�t�: Epsilon
//------------------------------------------------------------------------------
stock GET_PLAYER_NAME( id )
{
	// Egy adatt�rol� l�trehoz�sa a n�v t�rol�s�ra.
	new x[  MAX_PLAYER_NAME  ];

	// Ha a j�t�kos csatlakozva van akkor lek�rj�k a nev�t �s elhelyezz�k az x t�rol�ba.
	if( IsPlayerConnected( id ) ) GetPlayerName( id , x , sizeof(x) );

	// visszat�r�s az x �rt�k�vel.
	return x;
}

//------------------------------------------------------------------------------
// N�v: GET_PLAYER_IP
// Le�r�s: A j�t�kos ip c�m�t lehet vele egyszer�en lek�rni.
// K�sz�t�: Spatrik
//------------------------------------------------------------------------------
stock GET_PLAYER_IP(playerid)
{
	// Egy adatt�rol� l�trehoz�sa az ip t�rol�s�ra.
	new ip[16];

	// Ha a j�t�kos csatlakozva van akkor lek�rj�k az ip c�m�t �s elhelyezz�k az ip t�rol�ba.
	if(IsPlayerConnected(playerid)) GetPlayerIp(playerid, ip, 16);

	// visszat�r�s az ip �rt�k�vel.
	return ip;
}

//------------------------------------------------------------------------------
// N�v: KillPlayer
// Le�r�s: A j�t�kost lehet vele meg�lni.
// K�sz�t�: Spatrik
//------------------------------------------------------------------------------
stock KillPlayer(playerid)
{
	// A j�t�kos �let�t 0-ra �ll�tjuk.
	SetPlayerHealth(playerid, 0.0);
	
	// Visszat�r�s
	return 1;
}

//------------------------------------------------------------------------------
// N�v: GivePlayerScore
// Le�r�s: A j�t�kos pontjait lehet n�velni.
// K�sz�t�: Spatrik
//------------------------------------------------------------------------------
stock GivePlayerScore(playerid, score)
{
	// Lek�rj�k a j�t�kos pontjait �s hozz�adjuk az adott sz�mot.
	SetPlayerScore(playerid, GetPlayerScore(playerid) +score);
	
	// Visszat�r�s
	return 1;
}

//------------------------------------------------------------------------------
// N�v: GivePlayerHealth
// Le�r�s: Gy�gy�tja a j�t�kost megadott �rt�kkel.
// K�sz�t�: Epsilon
//------------------------------------------------------------------------------
stock GivePlayerHealth(id, Float:h)
{
	// Lebeg�pontos v�ltoz� l�trehoz�sa
    new Float:hp;
	// �letpontok lek�r�se �s t�rol�sa
    GetPlayerHealth(id, hp);
	// "Gy�gy�t�s"
    SetPlayerHealth(id, hp + h);
    // Visszat�r�s
    return 1;
}

//------------------------------------------------------------------------------
// N�v: OffMusic
// Le�r�s: Le�ll�t minden hanghat�st az adott j�t�kosnak.
// K�sz�t�: Epsilon
//------------------------------------------------------------------------------
stock OffMusic(id)
{
	// "�res" hang lej�tsz�sa a j�t�kosnak
	// Visszat�r�s
	return PlayerPlaySound(id, 1069, 0.0, 0.0, 0.0);
}
//------------------------------------------------------------------------------
// N�v: OffMusicForAll
// Le�r�s: Le�ll�t minden hanghat�st mindenkinek.
// K�sz�t�: Epsilon
//------------------------------------------------------------------------------
stock OffMusicForAll()
{
		// ciklus defin�l�sa "�res" hang lej�tsz�sa
	foreach(id,200) PlayerPlaySound(id, 1069, 0.0, 0.0, 0.0);
	return 1;
}
//------------------------------------------------------------------------------
// N�v: ReturnUser
// Le�r�s: Egy megadott n�vb�l visszat�r a j�t�kos azon�s�t�sz�m�val. ( ID )
// K�sz�t�: Epsilon
//------------------------------------------------------------------------------
stock ReturnUser(estr[])
{
	// ciklus l�trehoz�sa
    for(new id = 0; id <= MAX_PLAYERS; id++)
    {
	// Csatlakoz�sr�l val� megbizonyosod�s
        if(IsPlayerConnected(id))
	{
		// Karakterl�nc l�trehoz�sa
            new ename[MAX_PLAYER_NAME];
		// N�v lek�rdez�se �s r�ol�sa
	    GetPlayerName(id, ename, MAX_PLAYER_NAME);
		// Egyez�s keres�se a j�t�kosok �s a lek�rdezett n�v k�z�tt
	    if(!strcmp(ename, estr, true, strlen(estr))) return id;
	}
    }
    // Visszat�r�s
    return INVALID_PLAYER_ID;
}
//------------------------------------------------------------------------------
// N�v: GetVehicleDriver
// Le�r�s: Lek�ri a megadott j�rm� sof�r�t ha van.
// K�sz�t�: Epsilon
//------------------------------------------------------------------------------
stock GetVehicleDriver(vehid)
{
	// Keres�s �s meg�llap�t�s
    for(new id; id<MAX_PLAYERS; id++) if(GetPlayerState(id) == 2) if (IsPlayerInVehicle(id, vehid)) return id;
	// Visszat�r�s
    return INVALID_PLAYER_ID;
}

//------------------------------------------------------------------------------
// N�v: OffRPName
// Le�r�s: RP szerverekn�l ahol k�telez� a _ a n�vben hasznos.
//             Ez kiveszi a karakterl�ncb�l a _ jelet �gy chatben nem lesz l�that� vagy
//     		     f�jl�r�sn�l is seg�thet.
// K�sz�t�: Epsilon
//------------------------------------------------------------------------------
stock OffRPName(id)
{
	// Karakterl�n defin�l�sa
    new estr[MAX_PLAYER_NAME];
	// N�v lek�rdez�se �s t�rol�sa
    GetPlayerName(id,estr,MAX_PLAYER_NAME);
	// _ karakterek lecser�l�se
    for(new id = 0; id < MAX_PLAYER_NAME; id++) if (estr[id] == '_') estr[id] = ' ';
	 // Visszat�r�s
    return estr;
}

//------------------------------------------------------------------------------
// N�v: GivePlayerWantedLevel
// Le�r�s: A j�t�kos pontjait lehet n�velni.
// K�sz�t�: Spatrik
//------------------------------------------------------------------------------
stock GivePlayerWantedLevel(playerid, level)
{
	// Lek�rj�k a j�t�kos k�r�z�si szintj�t �s hozz�adjuk az adott sz�mot.
	SetPlayerWantedLevel(playerid, GetPlayerWantedLevel(playerid) +level);

	// Visszat�r�s
	return 1;
}

//------------------------------------------------------------------------------
// N�v: Cenzura
// Le�r�s: Egy adott sz�t lehet vele ki csillagozni egy karakterl�ncb�l.
// K�sz�t�: Epsilon
//------------------------------------------------------------------------------
stock Cenzura(const b[],c[])
{
	// Sz�veg �tn�z�se bet�k�nt.
	for(new d=0; d<128; d++)
	{
		// Ha az adott sz� szerepel a sz�vegben.
		if (strfind(c[d], b, true) == 0)
		{
			// Ha megtal�ltuk az adott sz�t akkor megkeress�k a sz�vegben.
			for(new a=0; a<128; a++)
			{
				// Ha megtal�ltuk akkor kicsillagozzuk.
				if (a >= d && a < d+strlen(b)) c[a]='*';
			}
		}
	}
	// Visszat�r�s
	return 1;
}

//------------------------------------------------------------------------------
// N�v: OnlinePlayers
// Le�r�s: Visszat�r a szerveren l�v� j�t�kosok sz�m�val.
// K�sz�t�: Spatrik
//------------------------------------------------------------------------------
stock OnlinePlayers()
{
	// L�trehozunk egy v�ltoz�t
	new players = 0;
	
	// Elind�tunk egy ciklust ami 0-t�l a max slotokig csin�l egy elj�r�st.
    for(new i = 0; i < GetMaxPlayers(); i++)
    {
        // Ha az adott sloton akt�v egy j�t�kos akkor a v�ltoz� �rt�k�t 1-el megn�velj�k.
        if(IsPlayerConnected(i)) players++;
    }
    // Visszat�r�s
    return players;
}

//------------------------------------------------------------------------------
// N�v: PlaySoundForAll
// Le�r�s: Minden j�t�kosnak lej�tszik egy adott hangot.
// K�sz�t�: Spatrik
//------------------------------------------------------------------------------
stock PlaySoundForAll(soundid)
{
	// Egy ciklus seg�ts�g�vel az �sszes j�t�kosnak elind�tjuk az adott hangot.
	for(new i = 0; i < OnlinePlayers(); i++) PlayerPlaySound(i, soundid, 0.0, 0.0, 0.0);

	// Visszat�r�s
	return 1;
}
//------------------------------------------------------------------------------
// N�v: IsSamePlayerTeam
// Le�r�s: Meg�llap�tja, hogy TeamKill t�rt�nt-e.
// K�sz�t�: Spatrik
//------------------------------------------------------------------------------
stock IsSamePlayerTeam(playerid, killerid)
{
	// Ha a gyilkos csapata egyezik az �ldozat csapat�val akkor visszat�r�nk az "igaz" �rt�kkel.
	if(GetPlayerTeam(playerid) == GetPlayerTeam(killerid)) return true;
	
	// Ha nem egyezik akkor visszat�r�nk a "hamis" �rt�kkel.
	return false;
}
//------------------------------------------------------------------------------
// N�v: DestroyAllVehicles
// Le�r�s: T�rli az �sszes j�rm�vet.
// K�sz�t�: Spatrik
//------------------------------------------------------------------------------
stock DestroyAllVehicles()
{
	// Egy ciklus seg�ts�g�vel t�r�lj�k a j�rm�veket.
	for(new v = 0; v > MAX_VEHICLES; v++) DestroyVehicle(v);

	// Visszat�r�s
	return 1;
}
//------------------------------------------------------------------------------
// N�v: IsTeamKill
// Le�r�s: Meg�llap�tja, hogy TeamKill t�rt�nt-e.
// Figyelmeztet�s: Haszn�ld az OnPLayerDeath() elj�r�s alatt!
//                    M�shol az IsSamePlayerTeam fgv.-t haszn�ld!
// K�sz�t�: Spatrik
//------------------------------------------------------------------------------
stock IsTeamKill(playerid, killerid)
{
	// Ha a gyilkos csapata egyezik az �ldozat csapat�val akkor visszat�r�nk az "igaz" �rt�kkel.
	if(SamePlayerTeam(playerid,killerid) return true;
	
	// Ha nem egyezik akkor visszat�r�nk a "hamis" �rt�kkel.
	return false;
}



//------------------------------------------------------------------------------
// N�v: KickEx
// Le�r�s: Kirugja a j�t�kost + �zenetet �r mindenkinek.
// K�sz�t�: Spatrik
//------------------------------------------------------------------------------
stock KickEx(playerid, textcolor, reason[])
{
	// T�rol� l�trehoz�sa.
	new kickmsg[128];
	
	// A sz�tk�ldend� �zenet megform�z�sa.
	format(kickmsg, 128, "%s kickelve lett a szerverr�l! (ok: %s)", GET_PLAYER_NAME(playerid), reason);
	
	// Megform�zott �zenet sz�tk�ld�se.
	SendClientMessageToAll(textcolor, kickmsg);
	
	// Majd a j�t�kos kirug�sa.
	Kick(playerid);

	// Visszat�r�s
	return 1;
}

//------------------------------------------------------------------------------
// N�v: WriteFile
// Le�r�s: A f�jlba lehet egyszer�en �rni.
// K�sz�t�: Spatrik
//------------------------------------------------------------------------------
stock WriteFile(file[], text[])
{
	// L�trehozunk egy t�rol�t.
	new File: WriteFile;
	
	// A t�rol�nak �rt�ket adunk.
	WriteFile = fopen(file, io_append);
	
	// Ha a f�jl nem l�tezik,
	if(!WriteFile)
	{
	    // Akkor l�trehozzuk.
	    new File: CreateFile;
		CreateFile = fopen(file, io_write);
		fclose(CreateFile);
		WriteFile = fopen(file, io_append);
	}
	// Bele�rjuk az adatokat.
   	fwrite(WriteFile, text);
   	
   	// Majd a f�jlt bez�rjuk.
	fclose(WriteFile);

	// Visszat�r�s
	return 1;
}

//------------------------------------------------------------------------------
// N�v: fcreate
// Le�r�s: F�jlt lehet vele l�trehozni.
// K�sz�t�: Spatrik
//------------------------------------------------------------------------------
stock fcreate(fname[], fformat[])
{
	// T�rol� l�tehoz�sa.
	new fstring[256];
	
	// F�jln�v megform�z�sa.
	format(fstring, 128, "%s.%s", fname, fformat);
	
	// Ha a f�jl l�tezik akkor visszat�r�nk egy hiba�zenettel.
	if(fexist(fstring)) return printf("[HIBA]: A fajl mar letezik!");
	
	// F�jl megnyit�sa �r�sra
  	new File: f = fopen(fstring, io_write);
  	
  	// Ha a f�jl sikeresen l�trej�tt,
	if(f)
	{
	    // Akkor bez�rjuk,
		fclose(f);
		
		// �s egy �zenetet k�ld�nk el.
		printf( "[SUCCES]: '%s.%s' nevu fajl letrehozva!", fname, fformat);
		
		// Visszat�r�s
		return 1;
	}
	// Ha a f�jl tov�bbra sem l�tezik
	else
	{
	    // Akkor egy hiba�zenetet k�ld�nk
		printf( "[HIBA]: '%s.%s' nevu fajl letrehozasa sikertelen!", fname, fformat);
	}
	// Majd kil�p�nk az elj�r�sb�l.
	return 0;
}

//------------------------------------------------------------------------------
// N�v: IsNumeric
// Le�r�s: Lellen�rzi, hogy az adott sz�veg sz�mjegy-e.
//------------------------------------------------------------------------------
stock IsNumeric(string[])
{
	// Egy ciklus seg�ts�g�vel lellen�rizz�k a sz�veget.
	for (new i = 0, j = strlen(string); i < j; i++)
	{
	    // Ha a sz�veg nem sz�mb�l �ll akkor visszat�r�s a "hamis" �rt�kkel.
		if (string[i] > '9' || string[i] < '0') return false;
	}
	// Ha a sz�veg sz�m akkor visszat�r�s az "igaz" �rt�kkel.
	return true;
}

//------------------------------------------------------------------------------
// N�v: AntiDeamx
// Le�r�s: Ezt nem tudja �rtelmezni a deamx ford�t� ez�rt a scriptet nem lehet visszaford�tani amelyben ez szerepel.
//------------------------------------------------------------------------------
stock AntiDeamx()
{
	new a[][15] =
	{ "?","?" };
	#pragma unused a
}

//------------------------------------------------------------------------------
// N�v: PlayerToPoint
// Le�r�s: Ha a j�t�kos egy adott ponthoz k�zel l�p akkor egy elj�r�st lehet ind�tani vele.
//------------------------------------------------------------------------------
stock PlayerToPoint(Float:radi, playerid, Float:x, Float:y, Float:z)
{
    if(IsPlayerConnected(playerid))
	{
		new Float:oldposx, Float:oldposy, Float:oldposz;
		new Float:tempposx, Float:tempposy, Float:tempposz;
		GetPlayerPos(playerid, oldposx, oldposy, oldposz);
		tempposx = (oldposx -x);
		tempposy = (oldposy -y);
		tempposz = (oldposz -z);
		if (((tempposx < radi) && (tempposx > -radi)) && ((tempposy < radi) && (tempposy > -radi)) && ((tempposz < radi) && (tempposz > -radi)))
			return 1;
	}
	return 0;
}

//------------------------------------------------------------------------------
// N�v: strsplit
// Le�r�s: A forr�ssztringet a megadott elv�laszt�k ment�n egy c�lkaraktert�mbben helyezi el.
//------------------------------------------------------------------------------
stock strsplit( const source[  ], dest[  ][  ], seprator )
{
	new aNum, len, li, i;
	while( i < strlen( source ) ){
	    if( source[ i ] == seprator || !source[ i ] ){
	        len = strmid( dest[ aNum ], source, li, i, 255 );
	        dest[ aNum ][ len ] = 0;
	        aNum++, li = i + 1;
	    }
	    i++;
	}
}

//------------------------------------------------------------------------------
// N�v: strcpy
// Le�r�s: A forr�ssztringet �tm�solja a c�lsztringbe.
//------------------------------------------------------------------------------
stock strcpy( dest[  ], const source[  ], max = 255, len = -1 )
{
	new i;
	if( len == -1 ) len = strlen( source );
	while( i < len && i < max && ( dest[ i ] = source[ i ] ) ) i++;
	dest[ i == max ? i - 1 : i ] = 0;
}

//------------------------------------------------------------------------------
// N�v: strtok
// Le�r�s: R�szekre osztja a forr�ssztringet a whitespace karakterek ment�n.
//------------------------------------------------------------------------------
stock strtok( const source[  ], &index )
{
	new length = strlen( source );
	while( index < length && source[ index ] <= ' ' ) index++;
	new offset = index,
	    result[ 255 ];
	while( index < length && source[ index ] > ' ' && ( index - offset ) < sizeof( result ) ){
	    result[ index ] = source[ index - offset ];
	    index++;
	}
	result[ index - offset ] = 0;
	return result;
}

//------------------------------------------------------------------------------
// N�v: sscanf
// Le�r�s: Az strtok-hoz hasonl�an r�szekre osztja a forr�ssztringet de nem csak sztringeket kezel.
//------------------------------------------------------------------------------
stock sscanf(string[], format[], {Float,_}:...)
{
	#if defined isnull
		if (isnull(string))
	#else
		if (string[0] == 0 || (string[0] == 1 && string[1] == 0))
	#endif
		{
			return format[0];
		}
	#pragma tabsize 4
	new
		formatPos = 0,
		stringPos = 0,
		paramPos = 2,
		paramCount = numargs(),
		delim = ' ';
	while (string[stringPos] && string[stringPos] <= ' ')
	{
		stringPos++;
	}
	while (paramPos < paramCount && string[stringPos])
	{
		switch (format[formatPos++])
		{
			case '\0':
			{
				return 0;
			}
			case 'i', 'd':
			{
				new
					neg = 1,
					num = 0,
					ch = string[stringPos];
				if (ch == '-')
				{
					neg = -1;
					ch = string[++stringPos];
				}
				do
				{
					stringPos++;
					if ('0' <= ch <= '9')
					{
						num = (num * 10) + (ch - '0');
					}
					else
					{
						return -1;
					}
				}
				while ((ch = string[stringPos]) > ' ' && ch != delim);
				setarg(paramPos, 0, num * neg);
			}
			case 'h', 'x':
			{
				new
					ch,
					num = 0;
				while ((ch = string[stringPos]) > ' ' && ch != delim)
				{
					switch (ch)
					{
						case 'x', 'X':
						{
							num = 0;
							continue;
						}
						case '0' .. '9':
						{
							num = (num << 4) | (ch - '0');
						}
						case 'a' .. 'f':
						{
							num = (num << 4) | (ch - ('a' - 10));
						}
						case 'A' .. 'F':
						{
							num = (num << 4) | (ch - ('A' - 10));
						}
						default:
						{
							return -1;
						}
					}
				}
				setarg(paramPos, 0, num);
			}
			case 'c':
			{
				setarg(paramPos, 0, string[stringPos++]);
			}
			case 'f':
			{
				setarg(paramPos, 0, _:floatstr(string[stringPos]));
			}
			case 'p':
			{
				delim = format[formatPos++];
				continue;
			}
			case '\'':
			{
				new
					end = formatPos - 1,
					ch;
				while ((ch = format[++end]) && ch != '\'') {}
				if (!ch)
				{
					return -1;
				}
				format[end] = '\0';
				if ((ch = strfind(string, format[formatPos], false, stringPos)) == -1)
				{
					if (format[end + 1])
					{
						return -1;
					}
					return 0;
				}
				format[end] = '\'';
				stringPos = ch + (end - formatPos);
				formatPos = end + 1;
			}
			case 'u':
			{
				new
					end = stringPos - 1,
					id = 0,
					bool:num = true,
					ch;
				while ((ch = string[++end]) && ch != delim)
				{
					if (num)
					{
						if ('0' <= ch <= '9')
						{
							id = (id * 10) + (ch - '0');
						}
						else
						{
							num = false;
						}
					}
				}
				if (num && IsPlayerConnected(id))
				{
					setarg(paramPos, 0, id);
				}
				else
				{
					string[end] = '\0';
					num = false;
					new
						name[MAX_PLAYER_NAME];
					id = end - stringPos;

					foreach (playerid)
					{
						GetPlayerName(playerid, name, sizeof (name));
						if (!strcmp(name, string[stringPos], true, id))
						{
							setarg(paramPos, 0, playerid);
							num = true;
							break;
						}
					}
					if (!num)
					{
						setarg(paramPos, 0, INVALID_PLAYER_ID);
					}
					string[end] = ch;
				}
				stringPos = end;
			}
			case 's', 'z':
			{
				new
					i = 0,
					ch;
				if (format[formatPos])
				{
					while ((ch = string[stringPos++]) && ch != delim)
					{
						setarg(paramPos, i++, ch);
					}
					if (!i)
					{
						return -1;
					}
				}
				else
				{
					while ((ch = string[stringPos++]))
					{
						setarg(paramPos, i++, ch);
					}
				}
				stringPos--;
				setarg(paramPos, i, '\0');
			}
			default:
			{
				continue;
			}
		}
		while (string[stringPos] && string[stringPos] != delim && string[stringPos] > ' ')
		{
			stringPos++;
		}
		while (string[stringPos] && (string[stringPos] == delim || string[stringPos] <= ' '))
		{
			stringPos++;
		}
		paramPos++;
	}
	do
	{
		if ((delim = format[formatPos++]) > ' ')
		{
			if (delim == '\'')
			{
				while ((delim = format[formatPos++]) && delim != '\'') {}
			}
			else if (delim != 'z')
			{
				return delim;
			}
		}
	}
	while (delim > ' ');
	return 0;
}

//------------------------------------------------------------------------------
// N�v: SetPlayerMoney
// Le�r�s: �t�rja a j�t�kos vagyon�t.
// K�sz�t�: Epsilon
//------------------------------------------------------------------------------
stock SetPlayerMoney( id, mani )
{
	// J�t�kos vagynon�nak null�z�sa
    ResetPlayerMoney( id );
	//�j p�nz�sszeg "utal�sa"
    GivePlayerMoney( id , mani );
	//Visszat�r�s
    return 1;
}

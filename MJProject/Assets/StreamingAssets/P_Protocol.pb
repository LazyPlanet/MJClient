
�X
P_Protocol.protoAdoter.AssetP_Asset.proto"-
Account
username (
password ("`

PaiElement*
	card_type (2.Adoter.Asset.CARD_TYPE

card_value (

card_index ("e
ItemElement4
inventory_type (2.Adoter.Asset.INVENTORY_TYPE
index (
	global_id ("C
User&
account (2.Adoter.Asset.Account
player_list ("�

PlayerProp
online (-
position (2.Adoter.Asset.POSITION_TYPE
room_id (0
	load_type (2.Adoter.Asset.LOAD_SCENE_TYPE5
game_oper_state (2.Adoter.Asset.GAME_OPER_TYPE
check_feng_gang (
check_jian_gang (
pai_oper_count (

has_tinged	 (
oper_count_tingpai
 ("�

GameRecord2
list (2$.Adoter.Asset.GameRecord.GameElement�
GameElement
	player_id (
score (C
details (22.Adoter.Asset.GameRecord.GameElement.DetailElementH
DetailElement
score ((
fan_type (2.Adoter.Asset.FAN_TYPE"F
RoomHistory
room_id (&
list (2.Adoter.Asset.GameRecord"�

CommonProp
	player_id (
local_server_id (
name (
iphoto (
level (:1:
gender (2.Adoter.Asset.GENDER_TYPE:GENDER_TYPE_MAN
diamond (
	huanledou (
room_card_count	 (
total_rounds
 (
total_win_rounds (
streak_wins (
score (
room_history ("�
PlayerCommonLimit9
elements (2'.Adoter.Asset.PlayerCommonLimit.ElementE
Element
common_limit_id (

time_stamp (
count ("}
PlayerCoolDown6
elements (2$.Adoter.Asset.PlayerCoolDown.Element3
Element
cool_down_id (

time_stamp ("*
MailAttachment
common_reward_id ("�
Mail
title (E
send_player (:0\347\263\273\347\273\237\351\202\256\344\273\266
content (
	send_time (
readed (0

attachment (2.Adoter.Asset.MailAttachment"I
ClientInfomation
	client_ip (
system (

phone_type ("�
Player-
common_prop (2.Adoter.Asset.CommonProp
	server_id (*
	inventory (2.Adoter.Asset.Inventory5
common_limit (2.Adoter.Asset.PlayerCommonLimit/
	cool_down (2.Adoter.Asset.PlayerCoolDown

login_time (
logout_time (
	sign_time (3
client_info	 (2.Adoter.Asset.ClientInfomation%
	mail_list
 (2.Adoter.Asset.Mail-
player_prop (2.Adoter.Asset.PlayerProp"�
	Inventory2
	inventory (2.Adoter.Asset.Inventory.Elementg
Element4
inventory_type (2.Adoter.Asset.INVENTORY_TYPE&
items (2.Adoter.Asset.Item_Item"
ItemEquipment
star (">
Meta'
type_t (2.Adoter.Asset.META_TYPE
stuff ("i
CreatePlayerF
type_t (2.Adoter.Asset.META_TYPE:META_TYPE_SHARE_CREATE_PLAYER
	player_id ("m
Login<
type_t (2.Adoter.Asset.META_TYPE:META_TYPE_C2S_LOGIN&
account (2.Adoter.Asset.Account"G
Logout=
type_t (2.Adoter.Asset.META_TYPE:META_TYPE_C2S_LOGOUT"a
	EnterGameA
type_t (2.Adoter.Asset.META_TYPE:META_TYPE_C2S_ENTER_GAME
	player_id ("�
Room
room_id (*
	room_type (2.Adoter.Asset.ROOM_TYPE
enter_password (*
options (2.Adoter.Asset.RoomOptions"�
RoomOptions,
model (2.Adoter.Asset.ROOM_MODEL_TYPE3
extend_type (2.Adoter.Asset.ROOM_EXTEND_TYPE
top_mutiple (

open_rands (:4"t

CreateRoomD
type_t (2.Adoter.Asset.META_TYPE:META_TYPE_SHARE_CREATE_ROOM 
room (2.Adoter.Asset.Room"�
	EnterRoomC
type_t (2.Adoter.Asset.META_TYPE:META_TYPE_SHARE_ENTER_ROOM 
room (2.Adoter.Asset.Room,

error_code (2.Adoter.Asset.ERROR_CODE6

enter_type (2".Adoter.Asset.EnterRoom.ENTER_TYPE"9

ENTER_TYPE
ENTER_TYPE_ENTER
ENTER_TYPE_CANCEL"V
Sign=
type_t (2.Adoter.Asset.META_TYPE:META_TYPE_SHARE_SIGN
success ("z
PlayerLuckyPlateD
type_t (2.Adoter.Asset.META_TYPE:META_TYPE_SHARE_LUCKY_PLATE
plate_id (
result ("�
RandomSaiziE
type_t (2.Adoter.Asset.META_TYPE:META_TYPE_SHARE_RANDOM_SAIZI:
reason_type (2%.Adoter.Asset.RandomSaizi.REASON_TYPE
	player_id (
random_result (%
pai (2.Adoter.Asset.PaiElement"=
REASON_TYPE
REASON_TYPE_START
REASON_TYPE_TINGPAI"]
SayHi?
type_t (2.Adoter.Asset.META_TYPE:META_TYPE_SHARE_SAY_HI
heart_count ("�
	GetRewardA
type_t (2.Adoter.Asset.META_TYPE:META_TYPE_C2S_GET_REWARD9
reason (2).Adoter.Asset.GetReward.GET_REWARD_REASON
	reward_id ("]
GET_REWARD_REASON!
GET_REWARD_REASON_DAILY_BONUS%
!GET_REWARD_REASON_DAILY_ALLOWANCE"�
PaiOperationLimit
	player_id (
from_player_id (
time_out (%
pai (2.Adoter.Asset.PaiElement.
	oper_type (2.Adoter.Asset.PAI_OPER_TYPE"�
PaiOperationList
	player_id (
from_player_id (
time_out (%
pai (2.Adoter.Asset.PaiElement.
	oper_list (2.Adoter.Asset.PAI_OPER_TYPE"�
PaiOperationF
type_t (2.Adoter.Asset.META_TYPE:META_TYPE_SHARE_PAI_OPERATION.
	oper_type (2.Adoter.Asset.PAI_OPER_TYPE-
position (2.Adoter.Asset.POSITION_TYPE&
pais (2.Adoter.Asset.PaiElement%
pai (2.Adoter.Asset.PaiElement"�
GameOperationG
type_t (2.Adoter.Asset.META_TYPE:META_TYPE_SHARE_GAME_OPERATION/
	oper_type (2.Adoter.Asset.GAME_OPER_TYPE
source_player_id (
destination_player_id ("w
BuySomethingF
type_t (2.Adoter.Asset.META_TYPE:META_TYPE_SHARE_BUY_SOMETHING
mall_id (
result ("�
	LoadSceneA
type_t (2.Adoter.Asset.META_TYPE:META_TYPE_C2S_LOAD_SCENE0
	load_type (2.Adoter.Asset.LOAD_SCENE_TYPE
scene_id ("a

PlayerList>
type_t (2.Adoter.Asset.META_TYPE:META_TYPE_S2C_PLAYERS
player_list ("}
PlayerInformationB
type_t (2.Adoter.Asset.META_TYPE:META_TYPE_S2C_PLAYER_INFO$
player (2.Adoter.Asset.Player"�
AlertMessageB
type_t (2.Adoter.Asset.META_TYPE:META_TYPE_S2C_ALERT_ERROR,

error_type (2.Adoter.Asset.ERROR_TYPE6
error_show_type (2.Adoter.Asset.ERROR_SHOW_TYPE,

error_code (2.Adoter.Asset.ERROR_CODE"�
LiuJu<
type_t (2.Adoter.Asset.META_TYPE:META_TYPE_S2C_LIUJU/
elements (2.Adoter.Asset.LiuJu.LJElementE
	LJElement
	player_id (%
pai (2.Adoter.Asset.PaiElement"�
	PaiNotifyA
type_t (2.Adoter.Asset.META_TYPE:META_TYPE_S2C_PAI_NOTIFY
	player_id (:
	data_type (2'.Adoter.Asset.PaiNotify.CARDS_DATA_TYPE-
pais (2.Adoter.Asset.PaiNotify.MutiPai.
pai (2!.Adoter.Asset.PaiNotify.SinglePaiD
MutiPai*
	card_type (2.Adoter.Asset.CARD_TYPE
cards (K
	SinglePai*
	card_type (2.Adoter.Asset.CARD_TYPE

card_value ("a
CARDS_DATA_TYPE
CARDS_DATA_TYPE_START
CARDS_DATA_TYPE_FAPAI
CARDS_DATA_TYPE_SYNC"�
CommonPropertyH
type_t (2.Adoter.Asset.META_TYPE:META_TYPE_SHARE_COMMON_PROPERTYB
reason_type (2-.Adoter.Asset.CommonProperty.SYNC_REASON_TYPE
	player_id (-
common_prop (2.Adoter.Asset.CommonProp"G
SYNC_REASON_TYPE
SYNC_REASON_TYPE_SELF
SYNC_REASON_TYPE_GET"�
PaiOperationAlertJ
type_t (2.Adoter.Asset.META_TYPE:!META_TYPE_S2C_PAI_OPERATION_ALERT:
pais (2,.Adoter.Asset.PaiOperationAlert.AlertElemente
AlertElement%
pai (2.Adoter.Asset.PaiElement.
	oper_list (2.Adoter.Asset.PAI_OPER_TYPE"�
SyncCommonLimitC
type_t (2.Adoter.Asset.META_TYPE:META_TYPE_S2C_COMMON_LIMIT5
common_limit (2.Adoter.Asset.PlayerCommonLimit"r
SyncCommonRewardD
type_t (2.Adoter.Asset.META_TYPE:META_TYPE_S2C_COMMON_REWARD
common_reward_id ("�
RoomInformation@
type_t (2.Adoter.Asset.META_TYPE:META_TYPE_S2C_ROOM_INFO9
player_list (2$.Adoter.Asset.RoomInformation.Playerf
Player-
position (2.Adoter.Asset.POSITION_TYPE-
common_prop (2.Adoter.Asset.CommonProp"�
GameCalculateE
type_t (2.Adoter.Asset.META_TYPE:META_TYPE_S2C_GAME_CALCULATE(
record (2.Adoter.Asset.GameRecord"m
GameInformation@
type_t (2.Adoter.Asset.META_TYPE:META_TYPE_S2C_GAME_INFO
banker_player_id (*u
ERR_USE_ITEM_TYPE
ERR_USE_ITEM_TYPE_SUCCESS !
ERR_USE_ITEM_TYPE_LEVEL_BELOW
ERR_USE_ITEM_TYPE_LEVEL_UP*J
ITEM_CHANGED_TYPE
ITEM_CHANGED_TYPE_GMT
ITEM_CHANGED_TYPE_MALL*S
DIAMOND_CHANGED_TYPE
DIAMOND_CHANGED_TYPE_GMT
DIAMOND_CHANGED_TYPE_MALL*�
POSITION_TYPE
POSITION_TYPE_NULL 
POSITION_TYPE_EAST
POSITION_TYPE_SOUTH
POSITION_TYPE_WEST
POSITION_TYPE_NORTH*
LOAD_SCENE_TYPE
LOAD_SCENE_TYPE_NULL
LOAD_SCENE_TYPE_START
LOAD_SCENE_TYPE_SUCCESS
LOAD_SCENE_TYPE_FAILED*B

ERROR_TYPE
ERROR_TYPE_NORMAL
ERROR_TYPE_INVENTORY_FULL*+
ERROR_SHOW_TYPE
ERROR_SHOW_TYPE_CHAT*�

ERROR_CODE
ERROR_SUCCESS 
ERROR_INNER
ERROR_DIAMOND_NOT_ENOUGH
ERROR_BEANS_NOT_ENOUGH
ERROR_INVENTORY_FULL
ERROR_REWARD_HAS_GOT
ERROR_HUANLEDOU_LIMIT
ERROR_MALL_NOT_FOUND
ERROR_ACTIVITY_NOT_OPEN
ERROR_CLIENT_DATA	
ERROR_HAS_NO_PLAYER

ERROR_ROOM_NOT_FOUNT
ERROR_ROOM_PASSWORD
ERROR_ROOM_IS_FULL
ERROR_ROOM_NOT_AVAILABLE
ERROR_ROOM_NO_PERMISSION
ERROR_ROOM_BEANS_MIN_LIMIT
ERROR_ROOM_BEANS_MAX_LIMIT
ERROR_ROOM_TYPE_NOT_FOUND
ERROR_ROOM_HAS_BEEN_IN
ERROR_GAME_NO_PERMISSION(
ERROR_GAME_PAI_UNSATISFIED)*�
	META_TYPE
META_TYPE_SHARE_BEGIN!
META_TYPE_SHARE_CREATE_PLAYER
META_TYPE_SHARE_CREATE_ROOM!
META_TYPE_SHARE_PAI_OPERATION"
META_TYPE_SHARE_GAME_OPERATION#
META_TYPE_SHARE_COMMON_PROPERTY!
META_TYPE_SHARE_BUY_SOMETHING
META_TYPE_SHARE_ENTER_ROOM
META_TYPE_SHARE_SIGN	
META_TYPE_SHARE_LUCKY_PLATE
 
META_TYPE_SHARE_RANDOM_SAIZI
META_TYPE_SHARE_SAY_HI
META_TYPE_SHARE_COUNT2
META_TYPE_C2S_BEGIN3
META_TYPE_C2S_LOGIN4
META_TYPE_C2S_LOGOUT5
META_TYPE_C2S_SELECT_SERVER6
META_TYPE_C2S_ENTER_GAME7
META_TYPE_C2S_GET_REWARD8
META_TYPE_C2S_LOAD_SCENE9
META_TYPE_C2S_COUNT�
META_TYPE_S2C_BEGIN�
META_TYPE_S2C_TICKET�
META_TYPE_S2C_SERVER_LIST�
META_TYPE_S2C_PLAYERS�
META_TYPE_S2C_PLAYER_INFO�
META_TYPE_S2C_ALERT_ERROR�
META_TYPE_S2C_LIUJU�
META_TYPE_S2C_PAI_NOTIFY�&
!META_TYPE_S2C_PAI_OPERATION_ALERT�
META_TYPE_S2C_COMMON_LIMIT� 
META_TYPE_S2C_COMMON_REWARD�
META_TYPE_S2C_ROOM_INFO�!
META_TYPE_S2C_GAME_CALCULATE�
META_TYPE_S2C_GAME_INFO�
META_TYPE_S2C_COUNT�*N
ROOM_MODEL_TYPE
ROOM_MODEL_TYPE_CLASSICAL
ROOM_MODEL_TYPE_MULTIPLE*�
ROOM_EXTEND_TYPE
ROOM_EXTEND_TYPE_ZHANLIHU
ROOM_EXTEND_TYPE_JIAHU!
ROOM_EXTEND_TYPE_XUANFENGGANG
ROOM_EXTEND_TYPE_BAOPAI
ROOM_EXTEND_TYPE_DUANMEN
ROOM_EXTEND_TYPE_QIYISE
ROOM_EXTEND_TYPE_BAOSANJIA*�
PAI_OPER_TYPE
PAI_OPER_TYPE_BEGIN 
PAI_OPER_TYPE_DAPAI
PAI_OPER_TYPE_HUPAI
PAI_OPER_TYPE_GANGPAI
PAI_OPER_TYPE_PENGPAI
PAI_OPER_TYPE_CHIPAI
PAI_OPER_TYPE_GIVEUP
PAI_OPER_TYPE_XUANFENG_FENG
PAI_OPER_TYPE_XUANFENG_JIAN
PAI_OPER_TYPE_ANGANGPAI	
PAI_OPER_TYPE_TINGPAI

PAI_OPER_TYPE_BAOPAI
PAI_OPER_TYPE_COUNT*y
GAME_OPER_TYPE
GAME_OPER_TYPE_NULL
GAME_OPER_TYPE_START
GAME_OPER_TYPE_LEAVE
GAME_OPER_TYPE_KICKOUT
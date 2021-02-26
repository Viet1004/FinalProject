import tweepy

consumer_key = 'TY9EAjgje5fP2cY1msdbLMF1T'
consumer_secret = 'wzR72efd3V5g5bMN9t7FO3l6lhwWya5m2HxWeOV2Mlftj15ETt'
access_token = '901352542470152192-bgPb0kT0uha8DaqnbZAQaJ0NNhCXgEd'
access_token_secret = '4LNlU1H80byXmL8uNBGNBl7EtG3GMqTRO9MwORtslSE0o'

def OAuth():
	try:
		auth = tweepy.OAuthHandler(consumer_key, consumer_secret)
		auth.set_access_token(access_token, access_token_secret)
		return auth
	except Exception as e:
		return None

oauth = OAuth()
api = tweepy.API(oauth)

api.update_status('Hello world')

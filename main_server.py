import flask
app = flask.Flask(__name__)
@app.route("/")
def index():
	return "hello world"
app.run(host="0.0.0.0", port=4321, debug=True)

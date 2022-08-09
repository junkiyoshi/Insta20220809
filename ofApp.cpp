#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(255);
	ofEnableDepthTest();
	ofSetLineWidth(1.5);

	this->frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->face.clear();
	this->frame.clear();
	
	float phi_deg_step = 3;
	float theta_deg_step = 1;

	for (int radius = 50; radius <= 350; radius += 25) {

		for (float phi_deg = 200; phi_deg < 340; phi_deg += phi_deg_step) {

			float param = ofNoise(radius * 0.005 - ofGetFrameNum() * 0.008);
			if (param > 0.45) {

				param = ofMap(param, 0.45, 1, 0, 1);
			}
			else {

				param = 0;
			}
			float theta_deg_start = 90 + ofMap(ofNoise(ofRandom(39), radius * 0.005 - ofGetFrameNum() * 0.008), 0, 1, -360, 360) * param;
			int frame_start_index = this->face.getNumVertices();

			for (float theta_deg = theta_deg_start - 15; theta_deg < theta_deg_start + 15; theta_deg += theta_deg_step) {

				auto index = this->face.getNumVertices();
				vector<glm::vec3> vertices;

				vertices.push_back(glm::vec3(
					radius * sin((theta_deg - theta_deg_step * 0.5) * DEG_TO_RAD) * cos((phi_deg + phi_deg_step * 0.5) * DEG_TO_RAD),
					radius * sin((theta_deg - theta_deg_step * 0.5) * DEG_TO_RAD) * sin((phi_deg + phi_deg_step * 0.5) * DEG_TO_RAD),
					radius * cos((theta_deg - theta_deg_step * 0.5) * DEG_TO_RAD)));
				vertices.push_back(glm::vec3(
					radius * sin((theta_deg - theta_deg_step * 0.5) * DEG_TO_RAD) * cos((phi_deg - phi_deg_step * 0.5) * DEG_TO_RAD),
					radius * sin((theta_deg - theta_deg_step * 0.5) * DEG_TO_RAD) * sin((phi_deg - phi_deg_step * 0.5) * DEG_TO_RAD),
					radius * cos((theta_deg - theta_deg_step * 0.5) * DEG_TO_RAD)));
				vertices.push_back(glm::vec3(
					radius * sin((theta_deg + theta_deg_step * 0.5) * DEG_TO_RAD) * cos((phi_deg + phi_deg_step * 0.5) * DEG_TO_RAD),
					radius * sin((theta_deg + theta_deg_step * 0.5) * DEG_TO_RAD) * sin((phi_deg + phi_deg_step * 0.5) * DEG_TO_RAD),
					radius * cos((theta_deg + theta_deg_step * 0.5) * DEG_TO_RAD)));
				vertices.push_back(glm::vec3(
					radius * sin((theta_deg + theta_deg_step * 0.5) * DEG_TO_RAD) * cos((phi_deg - phi_deg_step * 0.5) * DEG_TO_RAD),
					radius * sin((theta_deg + theta_deg_step * 0.5) * DEG_TO_RAD) * sin((phi_deg - phi_deg_step * 0.5) * DEG_TO_RAD),
					radius * cos((theta_deg + theta_deg_step * 0.5) * DEG_TO_RAD)));

				this->face.addVertices(vertices);
				this->frame.addVertices(vertices);

				this->face.addIndex(index + 0); this->face.addIndex(index + 1); this->face.addIndex(index + 3);
				this->face.addIndex(index + 0); this->face.addIndex(index + 3); this->face.addIndex(index + 2);

				this->frame.addIndex(index + 0); this->frame.addIndex(index + 2);
				this->frame.addIndex(index + 1); this->frame.addIndex(index + 3);
			}

			this->frame.addIndex(frame_start_index + 0); this->frame.addIndex(frame_start_index + 1);
			this->frame.addIndex(this->frame.getNumVertices() - 1); this->frame.addIndex(this->frame.getNumVertices() - 2);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(270);

	ofSetColor(0);
	this->face.draw();

	ofSetColor(255);
	this->frame.draw();

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}
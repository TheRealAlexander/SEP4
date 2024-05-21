import axios from "axios";

const API_BASE_URL = "http://broker:5202/Broker/";

class LiveScoreService {
  static async getLiveScore(id) {
    try {
      const response = await axios.get(API_BASE_URL + `LiveScore/${id}`);
      return response.data;
    } catch (error) {
      console.error("Error fetching live score:", error);
      throw error;
    }
  }

  static async getAllMatches() {
    try {
      const response = await axios.get(API_BASE_URL + `LiveScore`);
      return response.data;
    } catch (error) {
      console.error("Error fetching all matches:", error);
      throw error;
    }
  }
}

export default LiveScoreService;

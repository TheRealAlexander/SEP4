import axios from 'axios';

class LiveScoreService {
    static async getLiveScore(id) {
        try {
            const response = await axios.get(`http://localhost:5202/Broker/LiveScore/${id}`);
            return response.data;
        } catch (error) {
            console.error('Error fetching live score:', error);
            throw error;
        }
    }

    static async getAllMatches() {
        try {
            const response = await axios.get(`http://localhost:5202/Broker/LiveScore`);
            return response.data;
        } catch (error) {
            console.error('Error fetching all matches:', error);
            throw error;
        }
    }
}

export default LiveScoreService;
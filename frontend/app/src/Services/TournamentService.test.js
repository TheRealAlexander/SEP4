import axios from 'axios';
import {
    GetAllTournaments,
    CreateTournament,
    UpdateTournament,
    RemoveTournament,
    AddParticipant,
    RemoveParticipant
} from './TournamentService'; // replace with your actual file name

jest.mock('axios', () => ({
    post: jest.fn(),
    get: jest.fn(),
    put: jest.fn(),
    delete: jest.fn(),
  }));

describe('Tournament API', () => {
    it('fetches all tournaments', async () => {
        const mockedResponse = { 
          data: [
            {
              TournamentID: 'mocked-tournament-id-1',
              State: 1,
              TimeAndDate: new Date(),
              Description: 'Mocked tournament 1',
              FieldCount: 5,
              Format: 'Mocked format 1',
              Participants: ['participant1', 'participant2']
            },
            {
              TournamentID: 'mocked-tournament-id-2',
              State: 2,
              TimeAndDate: new Date(),
              Description: 'Mocked tournament 2',
              FieldCount: 6,
              Format: 'Mocked format 2',
              Participants: ['participant3', 'participant4']
            }
          ] 
        };
        axios.get.mockResolvedValue(mockedResponse);
      
        const result = await GetAllTournaments();
      
        expect(result).toEqual(mockedResponse.data);
        expect(axios.get).toHaveBeenCalledWith('http://broker:5202/broker/tournaments');
    });

    it('creates a tournament', async () => {
        const mockedResponse = {
            data: {
                TournamentID: 'mocked-tournament-id',
                State: 1,
                TimeAndDate: new Date(),
                Description: 'Mocked tournament',
                FieldCount: 5,
                Format: 'Mocked format',
                Participants: ['participant1', 'participant2']
            }
        };
        axios.post.mockResolvedValue(mockedResponse);

        const tournamentData = {
            TournamentID: 'mocked-tournament-id',
            State: 1,
            TimeAndDate: new Date(),
            Description: 'Mocked tournament',
            FieldCount: 5,
            Format: 'Mocked format',
            Participants: ['participant1', 'participant2']
        };
        const result = await CreateTournament(tournamentData);

        expect(result).toEqual(mockedResponse.data);
    });

    it('updates a tournament', async () => {
        const mockedResponse = {
            data: {
                TournamentID: 'mocked-tournament-id',
                State: 1,
                TimeAndDate: new Date(),
                Description: 'Mocked tournament',
                FieldCount: 5,
                Format: 'Mocked format',
                Participants: ['participant1', 'participant2']
            }
        };
        axios.put.mockResolvedValue(mockedResponse);

        const tournamentData = {
            TournamentID: 'mocked-tournament-id',
            State: 1,
            TimeAndDate: new Date(),
            Description: 'Mocked tournament',
            FieldCount: 5,
            Format: 'Mocked format',
            Participants: ['participant1', 'participant2']
        };
        const result = await UpdateTournament(tournamentData);

        expect(result).toEqual(mockedResponse.data);
    });

    it('removes a tournament', async () => {
        const mockedResponse = { data: {} };
        axios.delete.mockResolvedValue(mockedResponse);

        const tournamentID = 'mocked-tournament-id';
        const result = await RemoveTournament(tournamentID);

        expect(result).toEqual(mockedResponse.data);
    });

    it('adds a participant', async () => {
        const mockedResponse = {
            data: {
                TournamentID: 'mocked-tournament-id',
                State: 1,
                TimeAndDate: new Date(),
                Description: 'Mocked tournament',
                FieldCount: 5,
                Format: 'Mocked format',
                Participants: ['participant1', 'participant2', 'new-participant']
            }
        };
        axios.post.mockResolvedValue(mockedResponse);

        const tournamentID = 'mocked-tournament-id';
        const participant = 'new-participant';
        const result = await AddParticipant(tournamentID, participant);

        expect(result).toEqual(mockedResponse.data);
    });

    it('removes a participant', async () => {
        axios.delete.mockResolvedValue();

        const tournamentID = 'mocked-tournament-id';
        const participant = 'participant-to-remove';
        await RemoveParticipant(tournamentID, participant);

        expect(axios.delete).toHaveBeenCalledWith(`http://broker:5202/broker/tournaments/${tournamentID}/participants/${participant}`);
    });
});